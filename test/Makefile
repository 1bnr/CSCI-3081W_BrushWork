# some testing definitions
.PHONY: $(GOLDIR) $(SRCPNG) $(SRCJPG) golden gold_floats gold_ints gold_filter_chains build_floats build_ints build_filter_chains run_tests
.SILENT: gold_floats gold_ints gold_filter_chains build_floats build_ints build_filter_chains test_ints test_floats test_filter_chains
FEXT          = .jpg .png
MIA           = ./build/MIA/bin/MIA
GOLDIR        = ./test/golden_images/
BUILDDIR      = $(BUILDROOT)/$(notdir $(shell pwd))
GOLDPRE       = gold-
TESTDIR       = ./test/
SRCPNG        = src_images/snaily.png
SRCJPG        = src_images/snaily.jpg
FILTERS_NOA   = edge
FILTERS_FLT   = sharpen threshold blur saturate
FILTERS_INT   = quantize
INT_ARGS      = 2 5 9 10
FLT_ARGS      = 0.1 0.9 1.9 5.5

# make ./test/golden_images directory
$(GOLDIR):
	@mkdir $(GOLDIR)

# Define the lists of files of the gold images and the test images by
# finding all the .png and .jpg files in respective the directories.
GOLD_IMGS += $(wildcard $(GOLDIR)*.png)
GOLD_IMGS += $(wildcard $(GOLDIR)*.jpg)

TEST_IMGS += $(wildcard $(TESTDIR)*.png)
TEST_IMGS += $(wildcard $(TESTDIR)*.jpg)
rootdir =

all: run_tests


golden: gold_floats gold_ints gold_filter_chains| $(GOLDIR)

# initialize some variables
goldfile =
testfile =
ext =
filter =
num =

# make gold images for filters that use float args
gold_floats:
	cd ../ ; \
	for ext in $(FEXT); do \
		for filter in $(FILTERS_FLT); do \
			for num in $(FLT_ARGS); do \
			  goldfile=`echo $(GOLDIR)$(GOLDPRE)$$filter-$$num$$ext | sed "s/\./_/ 2"`; \
				if [ "$$filter" = "sharpen" ]; then \
					if [ $$(echo "$$num >= 0" | bc -l) -ne 0 ]; then \
						$(MIA) $(TESTDIR)$(SRCJPG) -$$filter $$num $$goldfile; \
					fi; \
				elif [ "$$filter" = "threshold" ]; then \
					if [ $$(echo "$$num <= 1 && $$num >= 0" | bc -l) -ne 0 ]; then \
						$(MIA) $(TESTDIR)$(SRCJPG) -$$filter $$num $$goldfile; \
					fi; \
				elif [ "$$filter" = "quantize" ]; then \
					if [ $$(echo "$$num >= 2" | bc -l) -ne 0 ]; then \
						$(MIA) $(TESTDIR)$(SRCJPG) -$$filter $$num $$goldfile; \
					fi; \
				elif [ "$$filter" = "blur" ]; then \
					if [ $$(echo "$$num >= 0" | bc -l) -ne 0 ]; then \
						$(MIA) $(TESTDIR)$(SRCJPG) -$$filter $$num $$goldfile; \
					fi; \
				elif  [ "$$filter" = "saturate" ]; then \
					$(MIA) $(TESTDIR)$(SRCJPG) -$$filter $$num $$goldfile; \
				fi; \
			done; \
		done ; \
	done

# make gold images for filters that take int args
gold_ints:
	cd ../ ; \
	for ext in $(FEXT); do \
		for num in $(INT_ARGS); do \
		goldfile=$(GOLDIR)$(GOLDPRE)$(FILTERS_INT)-$$num$$ext; \
			$(MIA) $(TESTDIR)$(SRCJPG) -$(FILTERS_INT) $$num $$goldfile; \
		done ; \
	done

# make gold images that use filter chains; float filters followed by int filter
gold_filter_chains:
	cd ../ ; \
		for ext in $(FEXT); do \
			for filter in $(FILTERS_FLT); do \
				goldfile=$(GOLDIR)$(GOLDPRE)-$$filter-0_3$(FILTERS_INT)_7-$$filter$$ext; \
				$(MIA) $(TESTDIR)$(SRCJPG) -$(FILTERS_INT) 7 -$$filter 0.3  $$goldfile; \
			done ; \
		done

# make test images that use float filters
build_floats:
	cd ../ ; \
	for ext in $(FEXT); do \
		for filter in $(FILTERS_FLT); do \
			for num in $(FLT_ARGS); do \
			  testfile=`echo $(TESTDIR)$$filter-$$num$$ext | sed "s/\./_/ 2"`; \
				if [ "$$filter" = "sharpen" ]; then \
					if [ $$(echo "$$num >= 0" | bc -l) -ne 0 ]; then \
						$(MIA) $(TESTDIR)$(SRCJPG) -$$filter $$num $$testfile; \
					fi; \
				elif [ "$$filter" = "threshold" ]; then \
					if [ $$(echo "$$num <= 1 && $$num >= 0" | bc -l) -ne 0 ]; then \
						$(MIA) $(TESTDIR)$(SRCJPG) -$$filter $$num $$testfile; \
					fi; \
				elif [ "$$filter" = "quantize" ]; then \
					if [ $$(echo "$$num >= 2" | bc -l) -ne 0 ]; then \
						$(MIA) $(TESTDIR)$(SRCJPG) -$$filter $$num $$testfile; \
					fi; \
				elif [ "$$filter" = "blur" ]; then \
					if [ $$(echo "$$num >= 0" | bc -l) -ne 0 ]; then \
						$(MIA) $(TESTDIR)$(SRCJPG) -$$filter $$num $$testfile; \
					fi; \
				elif  [ "$$filter" = "saturate" ]; then \
					$(MIA) $(TESTDIR)$(SRCJPG) -$$filter $$num $$testfile; \
				fi; \
			done; \
		done ; \
	done

# make test images that use int filter
build_ints:
	cd ../ ; \
	for ext in $(FEXT); do \
		for num in $(INT_ARGS); do \
		testfile=$(TESTDIR)$(FILTERS_INT)-$$num$$ext; \
			$(MIA) $(TESTDIR)$(SRCJPG) -$(FILTERS_INT) $$num $$testfile; \
		done ; \
	done

# make test images that use filter chains; float filters followed by int filter
build_filter_chains:
	cd ../ ; \
	for ext in $(FEXT); do \
		for filter in $(FILTERS_FLT); do \
			testfile=$(TESTDIR)-$$filter-0_3$(FILTERS_INT)_7-$$filter$$ext; \
			$(MIA) $(TESTDIR)$(SRCJPG) -$(FILTERS_INT) 7 -$$filter 0.3  $$testfile; \
		done ; \
	done

# run float filter tests
test_floats:
	cd ../ ; \
	for ext in $(FEXT); do \
		for filter in $(FILTERS_FLT); do \
			for num in $(FLT_ARGS); do \
			  testfile=`echo $(TESTDIR)$$filter-$$num$$ext | sed "s/\./_/ 2"`; \
				goldfile=`echo $(GOLDIR)$(GOLDPRE)$$filter-$$num$$ext | sed "s/\./_/ 2"`; \
				if [ "$$filter" = "sharpen" ]; then \
					if [ $$(echo "$$num >= 0" | bc -l) -ne 0 ]; then \
						$(MIA) $$testfile -compare $$goldfile; \
					fi; \
				elif [ "$$filter" = "threshold" ]; then \
					if [ $$(echo "$$num <= 1 && $$num >= 0" | bc -l) -ne 0 ]; then \
						$(MIA) $$testfile -compare $$goldfile; \
					fi; \
				elif [ "$$filter" = "quantize" ]; then \
					if [ $$(echo "$$num >= 2" | bc -l) -ne 0 ]; then \
						$(MIA) $$testfile -compare $$goldfile; \
					fi; \
				elif [ "$$filter" = "blur" ]; then \
					if [ $$(echo "$$num >= 0" | bc -l) -ne 0 ]; then \
						$(MIA) $$testfile -compare $$goldfile; \
					fi; \
				elif  [ "$$filter" = "saturate" ]; then \
					$(MIA) $$testfile -compare $$goldfile; \
				fi; \
			done; \
		done ; \
	done

# run the int filter tests
test_ints:
	cd ../ ; \
	for ext in $(FEXT); do \
		for num in $(INT_ARGS); do \
			testfile=$(TESTDIR)$(FILTERS_INT)-$$num$$ext; \
			goldfile=$(GOLDIR)$(GOLDPRE)$(FILTERS_INT)-$$num$$ext; \
			cd .. & $(MIA) $$testfile -compare $$goldfile; \
		done ; \
	done

# run filter chain tests; float filters followed by int filter
test_filter_chains:
	cd ../ ; \
	for ext in $(FEXT); do \
		for filter in $(FILTERS_FLT); do \
				testfile=$(TESTDIR)-$$filter-0_3$(FILTERS_INT)_7-$$filter$$ext; \
				goldfile=$(GOLDIR)$(GOLDPRE)-$$filter-0_3$(FILTERS_INT)_7-$$filter$$ext; \
				$(MIA) $$testfile -compare $$goldfile;  \
		done ; \
	done


build_test_files: build_ints build_floats build_filter_chains
	@echo "finished making test files"


# run all the tests
run_tests:
	@echo "making test images"
	@make build_test_files
	@echo "running tests"
	@make test_floats
	@make test_ints
	@make test_filter_chains
	@echo "completed all tests"


clean:
	cd ../ ; \
	for ext in $(FEXT); do \
		rm $(TESTDIR)*$$ext; \
	done

removegolden:
	cd ../ ; \
	pwd; \
	rm $(GOLDIR)gold*
	for ext in $(FEXT); do \
		rm $(TESTDIR)*$$ext; \
	done
