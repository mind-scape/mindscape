Summary: Platform Game
Name: mindscape
Version: 0.0.1
Release: 1
Source0: %{name}-%{version}.tar.gz
License: Various
Url: https://github.com/mind-scape/%{name}
BuildRequires: gcc, make, cmake, SDL2-devel, SDL2_image-devel, SDL2_ttf-devel, SDL2_mixer-devel

%description
Platform Game

%prep
%setup -q

%build
./control.sh build --make

%install

rm -rf $RPM_BUILD_ROOT
mkdir -p ${RPM_BUILD_ROOT}/usr/bin/
cp bin/mindscape ${RPM_BUILD_ROOT}/usr/bin/

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
/usr/bin/mindscape

%changelog
* Fri May 26 2017 Luan Guimarães <livreluan@gmail.com> - 0.0.1-1
- Initial package for CentOS
