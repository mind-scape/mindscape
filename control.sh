MAKE_ENABLED=false
INVALID_OPTIONS=false

validates_distro() {
  if [ "$COMMAND" == "package" ]; then
    if [ "$DISTRO" == "debian" ] || [ "$DISTRO" == "redhat" ]; then
      true
    else
      INVALID_OPTIONS=true
    fi
  else
    INVALID_OPTIONS=true
  fi
}

validates_tag() {
  if [ "$COMMAND" == "archive" ] || [ "$COMMAND" == "package" ]; then
    true
  else
    INVALID_OPTIONS=true
  fi
}

previous=
for i in "$@"; do
  case $i in
    build|make|run|all|clear|package|archive)
      COMMAND=$i
      shift
      ;;
    --make)
      MAKE_ENABLED=true
      shift
      ;;
    --distro)
      DISTRO=$2
      shift 2
      ;;
    --tag)
      TAG=$2
      shift 2
      ;;
    *)
      if [ -z "$COMMAND" ]; then
        INVALID_OPTIONS=true
      elif [ "$previous" == "--distro" ]; then
        validates_distro
      elif [ "$previous" == "--tag" ]; then
        validates_tag
      else
          INVALID_OPTIONS=true
      fi
      ;;
  esac
  previous=$i
done

if $INVALID_OPTIONS; then
  echo "E: missing command or invalid options" >&2
  echo "" >&2
  echo "Usage: `basename $0` <command> [options]" >&2
  echo "" >&2
  echo "* <command> = {build|make|run|all|clear}" >&2
  echo "* [options] = --make" >&2
  echo "              --distro <debian|redhat>" >&2
  echo "              --tag    <git-tag>" >&2
  exit 2
fi

do_build() {
# Remove existing build directory
  echo "Removing build dir"
  rm -rf build/

# Creating build directory
  echo "Creating build file"
  mkdir build

# Enter build and run Cmake
  echo "Running cmake"
  cd build && cmake ..
  cd ..
}

do_make() {
# Remove existing bin directory
  echo "Removing build dir"
  rm -rf bin
  
# Creating build directory
  echo "Creating build file"
  mkdir bin

# Running make
  echo "Running make command"
  cd build
  make

# Move binary files to bin folder
  echo "Moving binary files to bin directory"
  mv mindscape ../bin/
  
  cd ..
}

do_run() {
  cd bin
  ./mindscape
}

do_all() {
  do_build
  do_make
  do_run
}

do_archive(){
  echo "Creating archive."
  git archive --format=tar.gz --prefix=mindscape-${TAG:1}/ $TAG > mindscape-${TAG:1}.tar.gz
  mkdir -p archives
  mv mindscape-${TAG:1}.tar.gz archives/
  echo "Done."
}

do_clear() {
  rm -rf archives
  rm -rf build
  rm -rf bin
}

do_package() {
  generate_${DISTRO}_package
}

generate_debian_package() {
  echo "Generating debian package for TAG: $TAG"
  echo

  rm -rf .vagrant
  do_clear
  do_archive
  echo "Moving archives to parent directory."
  mv archives/mindscape-${TAG:1}.tar.gz ../

  echo "Cleaning directory"
  do_clear

  old_dir=`pwd`
  new_dir=mindscape-${TAG:1}
  echo "Renaming $old_dir to $new_dir"
  cd ..
  mv $old_dir $new_dir
  cd $new_dir

  echo "Running dh_make."
  do_clear
  dh_make -f ../mindscape-${TAG:1}.tar.gz

  echo "Running debuild."
  debuild -us -uc --source-option=--include-binaries

  echo "Renaming mindscape name to the older."
  cd ..
  mv $new_dir $old_dir
  cd $old_dir
}

generate_redhat_package(){
  echo "Generating rpm package for TAG: $TAG"
  echo
  
  do_archive
  cd rpm/
  ./packager.sh
  cd ..
}

if $MAKE_ENABLED && [ "$COMMAND" = 'build' ]; then
  do_build
  do_make
elif $MAKE_ENABLED && [ "$COMMAND" = 'run' ]; then
  do_make
  do_run
else
  do_$COMMAND
fi

exit 0
