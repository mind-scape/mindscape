MAKE_ENABLED=false
INVALID_OPTIONS=false

for i in "$@"; do
  case $i in
    build|make|run|all|clear)
      COMMAND=$i
      shift
      ;;
    --make)
      MAKE_ENABLED=true
      shift
      ;;
    *)
      if [ -z "$COMMAND" ]; then
        echo "COMMAND: $i"
        echo "COMMAND: $COMMAND"
        INVALID_OPTIONS=true
      fi
      ;;
  esac
done

if $INVALID_OPTIONS; then
  echo "E: missing command or invalid options" >&2
  echo "" >&2
  echo "Usage: `basename $0` <command> [options]" >&2
  echo "" >&2
  echo "* <command> = {build|make|run|all|clear}" >&2
  echo "* [options] = --make" >&2
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

do_clear() {
  rm -rf build
  rm -rf bin
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
