# some testing definitions
.PHONY: $(GOLDIR) test_passthrough batch_test golden create_test_images create_golden_images testimgs comparison_tests move_log read_log run_tests clean removegolden
.SILENT: comparison_tests batch_test create_golden_images create_test_images move_log read_log clean removegolden

	#test_passthrough  test_ints test_floats test_filter_chains move_log read_log clean golden removegolden create_test_images create_golden_images

FEXT          = .jpg .png
MIA           = ./build/MIA/bin/MIA
TESTDIR       = ./test/
BUILDDIR      = $(BUILDROOT)/$(notdir $(shell pwd))
TESTIMGS      = $(TESTDIR)images/test-
SRCPNG        = $(TESTDIR)src_images/snaily.png
SRCJPG        = $(TESTDIR)src_images/snaily.jpg
GOLDIR        = $(TESTDIR)golden_images/
GOLDIMG       = $(GOLDIR)gold-
FILTERS_NOA   = edge
FILTERS_FLT   = sharpen threshold blur saturate
FILTERS_INT   = quantize
INT_ARGS      = 2 5 9 10 15
FLT_ARGS      = 0.1 0.9 1.9 5.5

# make ./test/golden_images directory
$(GOLDIR):
	cd ../; \
	mkdir -p $(GOLDIR);

# initialize some variables
goldfile =
testfile =
ext =
filter =
num =
all:
	@echo "\ncreating test images.\n";
	@sleep 2;
	@make testimgs
	@echo "\nrunning comparison tests\n"
	@sleep 2
	@make run_tests


golden: | $(GOLDIR)
	@make create_golden_images

testimgs:
	@mkdir -p images/;
	@make create_test_images

# make gold images
create_golden_images:
	cd ../; \
	echo "\ncreating golden images with filters using float arguments\n"; \
	for ext in $(FEXT); do \
		for filter in $(FILTERS_FLT); do \
			for num in $(FLT_ARGS); do \
			  goldfile=`echo $(GOLDIMG)$$filter-$$num$$ext | sed "s/\./_/ 2"`; \
				if [ "$$filter" = "sharpen" ]; then \
					if [ $$(echo "$$num >= 0" | bc -l) -ne 0 ]; then \
						$(MIA) $(SRCJPG) -$$filter $$num $$goldfile; \
					fi; \
				elif [ "$$filter" = "threshold" ]; then \
					if [ $$(echo "$$num <= 1 && $$num >= 0" | bc -l) -ne 0 ]; then \
						$(MIA) $(SRCJPG) -$$filter $$num $$goldfile; \
					fi; \
				elif [ "$$filter" = "quantize" ]; then \
					if [ $$(echo "$$num >= 2" | bc -l) -ne 0 ]; then \
						$(MIA) $(SRCJPG) -$$filter $$num $$goldfile; \
					fi; \
				elif [ "$$filter" = "blur" ]; then \
					if [ $$(echo "$$num >= 0" | bc -l) -ne 0 ]; then \
						$(MIA) $(SRCJPG) -$$filter $$num $$goldfile; \
					fi; \
				elif  [ "$$filter" = "saturate" ]; then \
					$(MIA) $(SRCJPG) -$$filter $$num $$goldfile; \
				fi; \
			done; \
		done; \
	done; \
	echo "\ncreating golden images with filters using int arguments\n"; \
	for ext in $(FEXT); do \
		for num in $(INT_ARGS); do \
		goldfile=$(GOLDIMG)$(FILTERS_INT)-$$num$$ext; \
			$(MIA) $(SRCJPG) -$(FILTERS_INT) $$num $$goldfile; \
		done; \
	done; \
	echo "\ncreating golden images with chained filters\n"; \
	for ext in $(FEXT); do \
		for filter in $(FILTERS_FLT); do \
			goldfile=$(GOLDIMG)$$filter-0_3$(FILTERS_INT)_7-$$filter-0_3-edge$$ext; \
			$(MIA) $(SRCJPG) -$(FILTERS_INT) 7 -$$filter 0.3 -edge $$goldfile; \
		done; \
	done; \
	echo "\ncreating golden images with passthrough (copy/change filetype)\n"; \
	for ext in $(FEXT); do \
		$(MIA) $(SRCJPG) $(GOLDIMG)srcjpg$$ext; \
		$(MIA) $(SRCPNG) $(GOLDIMG)srcpng$$ext; \
	done; \


# create test images
create_test_images:
	cd ../; \
	echo "\ncreating test images using filters with float arguments\n"; \
	echo `pwd`; \
	for ext in $(FEXT); do \
		for filter in $(FILTERS_FLT); do \
			for num in $(FLT_ARGS); do \
			  testfile=`echo $(TESTIMGS)$$filter-$$num$$ext | sed "s/\./_/ 2"`; \
				if [ "$$filter" = "sharpen" ]; then \
					if [ $$(echo "$$num >= 0" | bc -l) -ne 0 ]; then \
						$(MIA) $(SRCJPG) -$$filter $$num $$testfile; \
					fi; \
				elif [ "$$filter" = "threshold" ]; then \
					if [ $$(echo "$$num <= 1 && $$num >= 0" | bc -l) -ne 0 ]; then \
						$(MIA) $(SRCJPG) -$$filter $$num $$testfile; \
					fi; \
				elif [ "$$filter" = "quantize" ]; then \
					if [ $$(echo "$$num >= 2" | bc -l) -ne 0 ]; then \
						$(MIA) $(SRCJPG) -$$filter $$num $$testfile; \
					fi; \
				elif [ "$$filter" = "blur" ]; then \
					if [ $$(echo "$$num >= 0" | bc -l) -ne 0 ]; then \
						$(MIA) $(SRCJPG) -$$filter $$num $$testfile; \
					fi; \
				elif  [ "$$filter" = "saturate" ]; then \
					$(MIA) $(SRCJPG) -$$filter $$num $$testfile; \
				fi; \
			done; \
		done; \
	done; \
	echo "\ncreating test images using filters\n"; \
	for ext in $(FEXT); do \
		for num in $(INT_ARGS); do \
		testfile=$(TESTIMGS)$(FILTERS_INT)-$$num$$ext; \
			$(MIA) $(SRCJPG) -$(FILTERS_INT) $$num $$testfile; \
		done; \
	done; \
	echo "\ncreating test images with chained filters using\n"; \
	for ext in $(FEXT); do \
		for filter in $(FILTERS_FLT); do \
			testfile=$(TESTIMGS)-$$filter-0_3$(FILTERS_INT)_7-$$filter-0_3-edge$$ext; \
			$(MIA) $(SRCJPG) -$(FILTERS_INT) 7 -$$filter 0.3 -edge $$testfile; \
		done; \
	done; \
	echo "\ncreating test images with passthrough (copy/change filetype)\n"; \
	for ext in $(FEXT); do \
		$(MIA) $(SRCJPG) $(TESTIMGS)srcjpg$$ext; \
		$(MIA) $(SRCPNG) $(TESTIMGS)srcpng$$ext; \
	done; \


# run comparison tests
comparison_tests:
	cd ../; \
	for ext in $(FEXT); do \
		for filter in $(FILTERS_FLT); do \
			for num in $(FLT_ARGS); do \
			  testfile=`echo $(TESTIMGS)$$filter-$$num$$ext | sed "s/\./_/ 2"`; \
				goldfile=`echo $(GOLDIMG)$$filter-$$num$$ext | sed "s/\./_/ 2"`; \
				if [ "$$filter" = "sharpen" ]; then \
					if [ $$(echo "$$num >= 0" | bc -l) -ne 0 ]; then \
						$(MIA) $$goldfile -compare $$testfile >> test/test_log.txt; \
					fi; \
				elif [ "$$filter" = "threshold" ]; then \
					if [ $$(echo "$$num <= 1 && $$num >= 0" | bc -l) -ne 0 ]; then \
						$(MIA) $$goldfile -compare $$testfile >> test/test_log.txt; \
					fi; \
				elif [ "$$filter" = "quantize" ]; then \
					if [ $$(echo "$$num >= 2" | bc -l) -ne 0 ]; then \
						$(MIA) $$goldfile -compare $$testfile >> test/test_log.txt; \
					fi; \
				elif [ "$$filter" = "blur" ]; then \
					if [ $$(echo "$$num >= 0" | bc -l) -ne 0 ]; then \
						$(MIA) $$goldfile -compare $$testfile >> test/test_log.txt; \
					fi; \
				elif  [ "$$filter" = "saturate" ]; then \
					$(MIA) $$testfile -compare $$goldfile >> test/test_log.txt; \
				fi; \
			done; \
		done; \
	done; \
	for ext in $(FEXT); do \
		for num in $(INT_ARGS); do \
			testfile=$(TESTIMGS)$(FILTERS_INT)-$$num$$ext; \
			goldfile=$(GOLDIMG)$(FILTERS_INT)-$$num$$ext; \
				$(MIA) $$goldfile -compare $$testfile >> test/test_log.txt; \
		done; \
	done; \
	for ext in $(FEXT); do \
		for filter in $(FILTERS_FLT); do \
				testfile=$(TESTIMGS)-$$filter-0_3$(FILTERS_INT)_7-$$filter-0_3-edge$$ext; \
				goldfile=$(GOLDIMG)$$filter-0_3$(FILTERS_INT)_7-$$filter-0_3-edge$$ext; \
					$(MIA) $$goldfile -compare $$testfile >> test/test_log.txt; \
		done; \
	done; \
	for ext in $(FEXT); do \
		$(MIA) $(GOLDIMG)srcjpg$$ext -compare $(TESTIMGS)srcjpg$$ext >> test/test_log.txt; \
		$(MIA) $(GOLDIMG)srcpng$$ext -compare $(TESTIMGS)srcpng$$ext >> test/test_log.txt; \
	done


batch_test:
	cd ../; \
	echo "batch testing edge detection filter"; \
	build/MIA/bin/MIA resources/test-images/brainstack/mrbrain-8bit0\#\#.png -edge $(TESTIMGS)brainstack-edge0\#\#.png; \
	echo "batch testing quantize filter"; \
	build/MIA/bin/MIA resources/test-images/brainstack/mrbrain-8bit0\#\#.png -quantize 3 $(TESTIMGS)brainstack-quantize0\#\#.png; \
	echo "batch testing image comparison"; \
	build/MIA/bin/MIA resources/test-images/brainstack/mrbrain-8bit0\#\#.png -compare resources/test-images/brainstack/mrbrain-8bit0\#\#.png; \

bad_commands:
	cd ../; \
	build/MIA/bin/MIA resources/test-images/snaily.foo bad-input-extension.jpg; \
	build/MIA/bin/MIA does/not/exist.jpg input-does-not-exist.jpg; \
	build/MIA/bin/MIA resources/test-images/colorCircles.png color-circles.foo; \
	build/MIA/bin/MIA resources/test-images/colorCircles.png does/not/exist.png; \
	build/MIA/bin/MIA -sharpen 5.0 missing-input-file.png; \
	build/MIA/bin/MIA resources/test-images/snaily.jpg -sharpen 5.0; \
	build/MIA/bin/MIA resources/test-images/snaily.jpg -compare 17 resources/test-images/snaily.jpg; \
	build/MIA/bin/MIA resources/test-images/snaily.jpg -channel 1.0 1.0bad-channel-parameters.png; \
	build/MIA/bin/MIA resources/test-images/snaily.jpg -edge 5.0 bad-edge-parameters.png; \
	build/MIA/bin/MIA resources/test-images/brainstack/mr-brain-8bit#\#.png bad-brainstack1/mr-brain8bit#\#.png
	build/MIA/bin/MIA resources/test-images/brainstack/mr-brain-8bit#\#\#.png bad-brainstack2/mr-brain8bit#\#.png
	build/MIA/bin/MIA resources/test-images/brainstack/bad-brainstack3/mr-brain8bit#\#\#.png
	build/MIA/bin/MIA resources/test-images/brainstack/mr-brain-8bit#\#\#.pngbad-brainstack4/


fails = ""
# run all the tests
run_tests: move_log
	@make comparison_tests
	@echo "\nrunning comparison tests\n"
	@make read_log
	@sleep 1
	@echo "\nrunning batch processing tests\n"
	@sleep 2
	@make batch_test
	@sleep 3
	@echo "\n\nthe following commands are all expected to fail.\n\n"
	@sleep 4;
	@make bad_commands
	@echo "test_log.txt excludes the intentionally failed tests."

clean:
	cd ../; \
	if [ -d "./test/images/" ]; then \
		echo "cleaning images folder"; \
		for ext in $(FEXT); do \
			rm $(TESTIMGS)*$$ext; \
		done; \
		rmdir test/images; \
	fi

removegolden:
	cd ../; \
	if [ -d "$(GOLDIR)" ]; then \
		rm $(GOLDIR)gold*; \
		rmdir $(GOLDIR); \
	fi; \
	for ext in $(FEXT); do \
		if [ -d "$(TESTDIR)images/" ]; then \
			rm $(TESTIMGS)*$$ext; \
			rmdir $(TESTDIR)images/; \
		fi; \
	done;

read_log:
	echo `pwd`;
	sed -n '/different/p' test_log.txt;
	echo "comparison tests run: " `grep -c '' test_log.txt`;
	fails=`grep -o 'different' test_log.txt | wc -l`; \
	echo $$fails; \
	if [ "$$fails" = "0" ]; then \
		echo "all comparison tests passed."; \
	elif [ "$$fails" = "1" ]; then \
		echo "$$fails comparison test failed :"; \
	else \
		echo "$$fails comparison tests failed: "; \
	fi;
	sed -n '/different/p' test_log.txt; \
	sleep 2

move_log:
	if [ -f ./test_log.txt ]; then \
    $$(mv ./test_log.txt ./test_log.txt.$$(date +%M%H%S)); \
  fi
