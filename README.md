BrushWork
=========

Support code for CSci-3081W project iteration #1.

Build the code by running

`$ make`

## Running the linter

It is assumed that prior to handing in any iteration of the project, you will
run the following command on all source files in your repository:

    python ext/cpplint/cpplint.py --linelength=81 <source files>

And that this command will report 0 errors found. You will be evaluated on an
all-or-nothing basis for this part of the project, so take care to do this.

## Makefile guidelines
When compiling, we suggest you use the following set of compile flags:

    -W -Wall -Wextra -Weffc++

We will not enforce this, but compiling with all compiler warnings enabled as
above will help reduce the amount of headaches you have to endure for
overlooking something simple in the code (especially the effc++ one). If you
want to be hardcore, add the following flag:

    -pedantic
## Makefile rules
All submitted makefiles must build the main target when invoked exactly as
follows:

    make


## git commit messages

- There should only ever be ONE scope/module affected per commit message.
- If you have an 'and' in a commit subject, consider breaking it into 2 commits.

These are examples of the quality of the commit messages we will be expecting.

* feat(onUrlChange): Added new event to $browser
  - forward popstate event if available
  - forward hashchange event if popstate not available
  - do polling when neither popstate nor hashchange available
  Breaks $browser.onHashChange, which was removed (use onUrlChange instead)

* docs(project): Updated fixed docs from Google Docs
  Couple of typos fixed:
  - indentation
  - batchLogbatchLog -> batchLog
  - start periodic checking
  - missing brace
