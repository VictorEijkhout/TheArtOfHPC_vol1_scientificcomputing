# -*- makefile -*-
################################################################
####
#### Makefile for git lab
####
################################################################

.PHONY: info
info ::
	@echo "================ Git demo rules"

##
## this is an auxiliary target
##
.PHONY: newrepo
newrepo :
	@source dodef \
	 && echo "==== Create a new repository"\
	 && note "Create a directory, and nake it into a repository" \
	 && do_cmd "mkdir newrepo" \
	 && do_cmd "cd newrepo" \
	 && do_cmd "git init"
clean ::
	@rm -rf newrepo

##
## here are all the useful things you can do
##
MAIN = 1
OUTEXT = runout
info ::
	@echo "make init"
.PHONY: init
ALLOUTS += init
init :
	@if [ ${MAIN} = 1 ] ; then make clean ; export ext=runout ; else export ext=out ; fi \
	 && ( \
	    make --no-print-directory newrepo MAIN=0 \
	     && source dodef \
	     && cd newrepo \
	     && do_cmd "ls -a" \
	     && do_cmd "git status" \
	     ) 2>&1 | sed '/^$$/d' | tee $@.$$ext \
	 && make --no-print-directory process TGT=$@.$$ext
.PHONY: process
process :
	@if [ -z "${TGT}" ] ; then \
	    echo "Suppy TGT variable" && exit 1 \
	    ; \
	fi \
	 && echo "================" && echo "output in: tee ${TGT}" \
	 && if [[ ${TGT} =~ .*runout ]] ; then \
	        python3 process.py ${TGT} \
	         && git add ${TGT}* \
	    ; fi

info ::
	@echo "make movemaster DIR=... : rename offensive branch"
.PHONY: movemaster
ALLOUTS += movemaster
movemaster :
	@if [ ${MAIN} = 1 ] ; then make clean ; export ext=runout ; else export ext=out ; fi \
	 && make --no-print-directory newrepo MAIN=0 >/dev/null 2>&1 \
	 && ( source dodef \
	     && cd newrepo \
	     && echo "==== Branch renaming" \
	     && note "See what the main branch is" \
	     && do_cmd "git status" \
	     && note "Rename this branch" \
	     && do_cmd "git branch -m main" \
	     && do_cmd "git status" \
	     ) 2>&1 | sed '/^$$/d' | tee $@.$$ext \
	 && make --no-print-directory process TGT=$@.$$ext

EMPTYURL = https://github.com/TACC/empty.git
info ::
	@echo "make emptyclone"
.PHONY: emptyclone
ALLOUTS += emptyclone
emptyclone :
	@if [ ${MAIN} = 1 ] ; then make clean ; export ext=runout ; else export ext=out ; fi \
	 && ( \
	    source dodef \
	     && echo "==== Clone a repository from github"\
	     && note "Clone an empty repository and check that it is indeed empty" \
	     && do_cmd "git clone ${EMPTYURL} empty" \
	     && do_cmd "cd empty" \
	     && do_cmd "ls -a" \
	     && do_cmd "git status" \
	     ) 2>&1 | sed '/^$$/d' | tee $@.$$ext \
	 && make --no-print-directory process TGT=$@.$$ext
clean ::
	@rm -rf empty cmd.out

info ::
	@echo "make firstfile"
.PHONY: firstfile
ALLOUTS += firstfile
firstfile :
	@if [ ${MAIN} = 1 ] ; then make clean ; export ext=runout ; else export ext=out ; fi \
	 && make --no-print-directory newrepo MAIN=0 >/dev/null 2>&1 \
	 && ( source dodef \
	     && cd newrepo \
	     && do_cmd "git branch -m main" \
	    ) \
	 && ( source dodef \
	     && cd newrepo \
	     && echo "==== Add a file"\
	     && note "1. Create a file; it will initually be untracked" \
	     && do_cmd "echo foo > firstfile" \
	     && do_cmd "git status" \
	     && note "2. Add the file to the local repository" \
	     && do_cmd "git add firstfile" \
	     && do_cmd "git status" \
	     && note "3. Commit these changes" \
	     && do_cmd "git commit -m \"adding first file\"" \
	     && do_cmd "git status" \
	     ) 2>&1 | sed '/^$$/d' | tee $@.$$ext \
	 && make --no-print-directory process TGT=$@.$$ext

info ::
	@echo "make changefirst"
.PHONY: changefirst
ALLOUTS += changefirst
changefirst :
	@if [ ${MAIN} = 1 ] ; then make clean ; export ext=runout ; else export ext=out ; fi \
	 && make --no-print-directory firstfile MAIN=0 >/dev/null 2>&1 \
	 && ( source dodef \
	     && cd newrepo \
	     && export file=firstfile \
	     && echo "==== Change existing file"\
	     && note "1. Make changes to a file that is tracked" \
	     && do_cmd "echo bar >> $$file" \
	     && do_cmd "cat $$file" \
	     && do_cmd "git status" \
	     && note "2. See what the changes were wrt the previously commit version" \
	     && do_cmd "git diff $$file" \
	     && note "3. Commit the changes to the local repo" \
	     && do_cmd "git add $$file" \
	     && do_cmd "git commit -m \"changes to first file\"" \
	     && do_cmd "git status" \
	     && note "4. Get the log of all commits so far" \
	     && do_cmd "git log " \
	     ) 2>&1 | sed '/^$$/d' | tee $@.$$ext \
	 && make --no-print-directory process TGT=$@.$$ext

info ::
	@echo "make undofirst"
.PHONY: undofirst
ALLOUTS += undofirst
undofirst :
	@if [ ${MAIN} = 1 ] ; then make clean ; export ext=runout ; else export ext=out ; fi \
	 && make --no-print-directory changefirst MAIN=0 >/dev/null 2>&1 \
	 && ( source dodef \
	     && cd newrepo \
	     && export file=firstfile \
	     && echo "==== Undo changes in existing file"\
	     && note "1. Make regrettable changes" \
	     && do_cmd "echo bar >> $$file" \
	     && do_cmd "cat $$file" \
	     && do_cmd "git status" \
	     && do_cmd "git diff $$file" \
	     && note "2. Restore previously committed version" \
	     && do_cmd "git checkout $$file" \
	     && do_cmd "cat $$file" \
	     && do_cmd "git status" \
	     ) 2>&1 | sed '/^$$/d' | tee $@.$$ext \
	 && make --no-print-directory process TGT=$@.$$ext

info ::
	@echo "make revertfirst"
.PHONY: revertfirst
ALLOUTS += revertfirst
revertfirst :
	@if [ ${MAIN} = 1 ] ; then make clean ; export ext=runout ; else export ext=out ; fi \
	 && make --no-print-directory changefirst MAIN=0 >/dev/null 2>&1 \
	 && ( source dodef \
	     && cd newrepo \
	     && export file=firstfile \
	     && echo "==== Revert committed file"\
	     && note "1. Find the commit id that you want to roll back" \
	     && do_cmd "git log" \
	     && do_cmd "git show HEAD" \
	     && do_quiet "commit=$$( git show HEAD | awk 'NR==1 {print $$2}' )" \
	     && note "2. Use 'git revert' to roll back" \
	     && do_cmd "git revert \$$commit --no-edit" \
	     && note "3. See that we have indeed undone the commit" \
	     && do_cmd "cat $$file" \
	     && do_cmd "git status" \
	     && note "4. But there will be an entry in the log" \
	     && do_cmd "git log" \
	     ) 2>&1 | sed '/^$$/d' | tee $@.$$ext \
	 && make --no-print-directory process TGT=$@.$$ext

info ::
	@echo "make cfile"
.PHONY: cfile
ALLOUTS += cfile
cfile :
	@if [ ${MAIN} = 1 ] ; then make clean ; export ext=runout ; else export ext=out ; fi \
	 && make --no-print-directory newrepo MAIN=0 >/dev/null 2>&1 \
	 && cc=clang \
	 && ( source dodef \
	     && cd newrepo \
	     && echo "==== Dealing with source / object files" \
	     && do_cmd "echo \"int main(){}\" > cfile.c" \
	     && note "1. Add a source file to the repo" \
	     && do_cmd "git add cfile.c" \
	     && do_cmd "$$cc -c cfile.c" \
	     && do_cmd "$$cc -o cprog cfile.o" \
	     && do_cmd "git status" \
	     && note "2. Keep object files out of the repo" \
	     && do_cmd "echo \"*.o\" >> .gitignore" \
	     && do_cmd "echo cprog >> .gitignore" \
	     && do_cmd "git status" \
	     && do_cmd "git status --ignored" \
	     ) 2>&1 | sed '/^$$/d' | tee $@.$$ext \
	 && make --no-print-directory process TGT=$@.$$ext

TINKERURL = git@github.com:TACC/tinker.git
info ::
	@echo "make remotefile"
.PHONY: remotefile
ALLOUTS += remotefile
remotefile :
	@if [ ${MAIN} = 1 ] ; then make clean ; export ext=runout ; else export ext=out ; fi \
	 && make --no-print-directory newrepo MAIN=0 >/dev/null 2>&1 \
	 && ( source dodef \
	     && cd newrepo \
	     && git init && git branch -M main \
	     && if [ $$( git remote show | wc -l ) -gt 0 ] ; then \
	            git remote remove mainserver ; fi \
	     && git remote add mainserver ${TINKERURL} \
	     && git pull mainserver main \
	     && if [ $$( ls | wc -l ) -gt 0 ] ; then \
	            git rm * && git commit -m cleaning \
	             && git push --set-upstream mainserver main \
	        ; fi \
	     && git remote remove mainserver \
	    ) \
	 && ( source dodef \
	     && cd newrepo \
	     && echo "==== Push a file to remote site"\
	     && do_quiet "git branch -M main" \
	     && do_quiet "echo foo > newfile" \
	     && note "1. Committed changes" \
	     && do_cmd "git add newfile && git commit -m \"adding first file\"" \
	     && note "2. Connect local repo to a remote one" \
	     && do_cmd "git remote add mainserver ${TINKERURL}" \
	     && do_cmd "git remote -v" \
	     && note "3. Push changes" \
	     && do_cmd "git push -u mainserver main" \
	     && note "4. Further changes go there by default" \
	     && do_cmd "echo bar >> newfile && git add -u :. && git commit -m more && git push" \
	     ) 2>&1 | sed '/^$$/d' | tee $@.$$ext \
	 && make --no-print-directory process TGT=$@.$$ext

info ::
	@echo "make collab"
.PHONY: collab
ALLOUTS += collab
collab :
	@if [ ${MAIN} = 1 ] ; then make clean ; export ext=runout ; else export ext=out ; fi \
	 && make --no-print-directory remotefile MAIN=0 >/dev/null 2>&1 \
	 && ( source dodef \
	     && echo "==== Collaboration ====" \
	     && note "1. Person 1 makes a clone" \
	     && do_cmd "git clone ${TINKERURL} person1" \
	     && note "2. Person 2 makes a clone" \
	     && do_cmd "git clone ${TINKERURL} person2" \
	     && note "3. Person 1 adds a file and pushes it" \
	     && do_cmd "( cd person1 && echo 123 >> p1 && git add p1 && git commit -m \"add p1\" && git push ) " \
	     && note "4. Person 2 pulls, getting the new file" \
	     && do_cmd "( cd person2 && git pull )" \
	     ) 2>&1 | sed '/^$$/d' | tee $@.$$ext \
	 && make --no-print-directory process TGT=$@.$$ext
clean ::
	@rm -rf person1 person2

info ::
	@echo "make merge"
.PHONY: merge
ALLOUTS += merge
merge :
	@if [ ${MAIN} = 1 ] ; then make clean ; export ext=runout ; else export ext=out ; fi \
	 && make --no-print-directory remotefile MAIN=0 >/dev/null 2>&1 \
	 && export longfile="fourlines" \
	 && ( source dodef \
	     && do_cmd "git clone ${TINKERURL} person1" \
	     && do_cmd "git clone ${TINKERURL} person2" \
	     && do_cmd "( cd person1 && ( echo 1; echo 2; echo 3; echo 4 ) > $$longfile && git add $$longfile && git commit -m \"long file\" && git push ) " \
	     && do_cmd "( cd person2 && git pull )" \
	    ) \
	 && ( source dodef \
	     && echo "==== Non-conflicting changes ====" \
	     && note "1. We have a four line file" \
	     && do_cmd "cat person1/$$longfile" \
	     && note "2. Person 1 makes a change" \
	     && do_cmd "( cd person1 && sed -i -e '1s/1/one/' $$longfile && cat $$longfile ) " \
	     && note "3. Person 1 pushes the change" \
	     && do_cmd "( cd person1 && git add $$longfile && git commit -m \"edit line one\" && git push ) " \
	     && note "4. Person 2 makes a different change to the same file" \
	     && do_cmd "( cd person2 && sed -i -e '4s/4/four/' $$longfile && cat $$longfile ) " \
	     && note "5. This change does not conflict, we can pull/push" \
	     && do_cmd "( cd person2 && git add $$longfile && git commit -m \"edit line four\" && git pull --no-edit && git push ) " \
	     && note "6. Person 1 pulls to get all the changes" \
	     && do_cmd "( cd person1 && git pull && cat $$longfile )" \
	     ) 2>&1 | sed '/^$$/d' | tee $@.$$ext \
	 && make --no-print-directory process TGT=$@.$$ext

info ::
	@echo "make conflict"
.PHONY: conflict
ALLOUTS += conflict
conflict :
	@if [ ${MAIN} = 1 ] ; then make clean ; export ext=runout ; else export ext=out ; fi \
	 && make --no-print-directory remotefile MAIN=0 >/dev/null 2>&1 \
	 && export longfile="fourlines" \
	 && ( source dodef \
	     && do_cmd "git clone ${TINKERURL} person1" \
	     && do_cmd "git clone ${TINKERURL} person2" \
	     && do_cmd "( cd person1 && ( echo 1; echo 2; echo 3; echo 4 ) > $$longfile && git add $$longfile && git commit -m \"long file\" && git push ) " \
	     && do_cmd "( cd person2 && git pull )" \
	    ) \
	 && ( source dodef \
	     && echo "==== Conflict between changes ====" \
	     && note "1. We have a four line file" \
	     && do_cmd "cat person1/$$longfile" \
	     && note "2. Person 1 makes a change" \
	     && do_cmd "( cd person1 && sed -i -e '1s/1/one/' $$longfile && git add $$longfile && git commit -m \"edit line one\" && git push ) " \
	     && note "3. Person 2 makes a different change to the same file" \
	     && do_cmd "( cd person2 && sed -i -e '2s/2/two/' $$longfile && cat $$longfile  && git add $$longfile && git commit -m \"edit line two\" ) " \
	     && note "4. This change conflicts, we get an error" \
	     && do_cmd "( cd person2 && git pull --no-edit || echo ) " \
	     && note "5. The file now has both versions, and you can edit it" \
	     && do_cmd "( cd person2 && cat fourlines )" \
	     ) 2>&1 | sed '/^$$/d' | tee $@.$$ext \
	 && make --no-print-directory process TGT=$@.$$ext

info ::
	@echo "make devbranch"
.PHONY: devbranch
ALLOUTS += devbranch
devbranch :
	@if [ ${MAIN} = 1 ] ; then make clean ; export ext=runout ; else export ext=out ; fi \
	 && make --no-print-directory firstfile MAIN=0 >/dev/null 2>&1 \
	 && ( source dodef \
	     && cd newrepo \
	     && echo "==== Branching"\
	     && note "1. We have a file, committed and all" \
	     && do_cmd "cat firstfile" \
	     && do_cmd "git status" \
	     && note "2. Make a development branch" \
	     && do_cmd "git branch dev && git branch -a" \
	     && do_cmd "git checkout dev && git branch -a" \
	     && note "3. Make changes and commit them to the dev branch" \
	     && do_cmd "cat firstfile" \
	     && do_cmd "echo bar > firstfile && cat firstfile" \
	     && do_cmd "git status" \
	     && do_cmd "git add firstfile && git commit -m \"dev changes\" " \
	     && note "4. The other branch is still unchanged" \
	     && do_cmd "git checkout main && cat firstfile && git status" \
	     && note "5. We can check differences between branches" \
	     && do_cmd "git diff main dev" \
	     ) 2>&1 | sed '/^$$/d' | tee $@.$$ext \
	 && make --no-print-directory process TGT=$@.$$ext

info ::
	@echo "make devmerge"
.PHONY: devmerge
ALLOUTS += devmerge
devmerge :
	@if [ ${MAIN} = 1 ] ; then make clean ; export ext=runout ; else export ext=out ; fi \
	 && make --no-print-directory firstfile MAIN=0 >/dev/null 2>&1 \
	 && export longfile="fourlines" \
	 && ( source dodef \
	     && cd newrepo \
	     && do_cmd "( echo 1; echo 2; echo 3; echo 4 ) > $$longfile && git add $$longfile && git commit -m \"long file\" " \
	    ) \
	 && ( source dodef \
	     && cd newrepo \
	     && echo "==== Branch merging" \
	     && note "1. We have a file, committed and all" \
	     && do_cmd "cat $$longfile" \
	     && do_cmd "git status" \
	     && note "2. Make a development branch" \
	     && do_cmd "git branch dev && git checkout dev" \
	     && note "3. Make a change in the main branch" \
	     && do_cmd "git checkout main" \
	     && do_cmd "sed -i -e '1s/1/one/' $$longfile && cat $$longfile " \
	     && do_cmd "git add $$longfile && git commit -m \"edit line 1\" " \
	     && note "4. A different change elsewhere in the file" \
	     && do_cmd "git checkout dev" \
	     && do_cmd "sed -i -e '4s/4/four/' $$longfile && cat $$longfile " \
	     && do_cmd "git add $$longfile && git commit -m \"edit line 4\" " \
	     && note "5. Merge the dev branch into the main one" \
	     && do_cmd "git checkout main" \
	     && do_cmd "git merge dev" \
	     && do_cmd "cat $$longfile" \
	     && note "6. Check the current state" \
	     && do_cmd "git status && git log" \
	     ) 2>&1 | sed '/^$$/d' | tee $@.$$ext \
	 && make --no-print-directory process TGT=$@.$$ext

####
#### Regenerate all runout files
####
info ::
	@echo "================" && echo "make allouts"
.PHONY: allouts
allouts :
	@for a in ${ALLOUTS} ; do \
	    make --no-print-directory $$a \
	    ; \
	done \
	 && for r in *.runout* ; do \
	        sed -i "" -e 's?/Users/eijkhout/Current/istc/scientific-computing-private/other?/users/demo?' $$r \
	    ; done \
	 && git add *.runout*

include ../../makefiles/Make.clean
clean ::
	@rm -f *.out
totalclean :: clean
	@rm -rf *.runout
