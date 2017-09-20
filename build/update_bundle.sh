#!/bin/bash

APP_NAME=`cat ../sources/appversion.h | tr -d '\r\n\t \""' | sed -e 's/.*PRODUCTNAME\([a-zA-Z0-9]*\).*/\1/'`
APP_BUNDLE="${APP_NAME}.app"
OUTPUT="../bin"

if [ ! -d "$OUTPUT/$APP_BUNDLE" ]
then
echo "Error : no bundle found in the bin folder"
exit -1
fi

pushd $OUTPUT

ALL_DEPS=""

copy_deps() {
	for dep in `otool -L "$1" | sed -n 's/\(.*[^\\ ]\) (.*/\1/gp'`
	do
		current_dep=$(basename $dep)
		if [[ $dep =~ libwx ]]
		then
			oldfile=$dep
			oldlink=$dep
			newfile=$dep
			while [ -L $newfile ]
			do
				newfile=`readlink $newfile`
				if ! echo $newfile | grep '^/'
				then
					newfile=$(dirname $oldfile)/$newfile
				fi
				oldfile=$newfile
			done
			dep=$newfile
			current_dep=$(basename $dep)
			install_name_tool -change $oldlink "@executable_path/$current_dep" $1
			if [[ ! $ALL_DEPS =~ $current_dep ]]
			then
				ALL_DEPS="$ALL_DEPS $current_dep"
				echo "Copying $dep"
				cp "$dep" "$APP_BUNDLE/Contents/MacOS/"
				install_name_tool -id "@executable_path/$current_dep" "$APP_BUNDLE/Contents/MacOS/$current_dep"
				copy_deps "$APP_BUNDLE/Contents/MacOS/$current_dep"
			fi
		fi
	done
}
copy_deps "${APP_BUNDLE}/Contents/MacOS/$APP_NAME"

popd
