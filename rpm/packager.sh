#! /bin/bash

PACKAGE_NAME="mindscape"

# Install Development Tools
sudo yum groupinstall "Development Tools" 
sudo yum install rpm-build rpmdevtools
sudo yum install the_silver_searcher

# Generate RPM package tree
rpmdev-setuptree

sleep 2

# Move Tarball to the RPM SOURCE dir
cp ../archives/*.tar.gz $HOME/rpmbuild/SOURCES
cp *.spec   $HOME/rpmbuild/SPECS

# Generate rpm package
rpmbuild -ba $PACKAGE_NAME.spec
