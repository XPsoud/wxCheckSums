#!/bin/bash
VOLUME_SIZE=15m
APP_NAME=`cat ../sources/appversion.h | tr -d '\r\n\t \""' | sed -e 's/.*PRODUCTNAME\([a-zA-Z0-9]*\).*/\1/'`
#echo "APP_NAME          = ${APP_NAME}"
APP_VERSION_MAJOR=`cat ../sources/appversion.h | tr -d '\r\n\t ' | sed -e 's/.*VERSION_MAJOR\([0-9]*\).*/\1/'`
#echo "APP_VERSION_MAJOR = ${APP_VERSION_MAJOR}"
APP_VERSION_MINOR=`cat ../sources/appversion.h | tr -d '\r\n\t ' | sed -e 's/.*VERSION_MINOR\([0-9]*\).*/\1/'`
#echo "APP_VERSION_MINOR = ${APP_VERSION_MINOR}"
APP_VERSION_REV=`cat ../sources/appversion.h | tr -d '\r\n\t ' | sed -e 's/.*VERSION_REV\([0-9]*\).*/\1/'`
#echo "APP_VERSION_REV   = ${APP_VERSION_REV}"
APP_VERSION_BUILD="201"`cat ../sources/appversion.h | tr -d '\r\n\t ' | sed -e 's/.*VERSION_BUILD\([0-9]*\).*/\1/'`
#echo "APP_VERSION_BUILD = ${APP_VERSION_BUILD}"
APP_VERSION_FULL=$APP_VERSION_MAJOR.$APP_VERSION_MINOR.$APP_VERSION_REV
#echo "APP_VERSION_FULL  = ${APP_VERSION_FULL}"
VOLUME_NAME="${APP_NAME}-v${APP_VERSION_FULL}_${APP_VERSION_BUILD}_OSX64"
APP_BUNDLE="${APP_NAME}.app"
DMG_NAME="${VOLUME_NAME}.dmg"
OUTPUT="../bin"

echo "Starting creation of disk image named ${DMG_NAME}"
if [ ! -d "$OUTPUT/$APP_BUNDLE" ]
then
echo "Error : no bundle found in the bin folder"
echo "$OUTPUT/$APP_BUNDLE"
exit -1
fi

pushd $OUTPUT

DMG_TMP_NAME="${VOLUME_NAME}-tmp.dmg"

echo "Creating DMG temp file '${DMG_TMP_NAME}'"
hdiutil create -srcfolder "${APP_BUNDLE}" \
                -volname "${VOLUME_NAME}" \
                -fs HFS+ \
                -fsargs "-c c=64,a=16,e=16" \
                -format UDRW \
                -size ${VOLUME_SIZE} \
                ${DMG_TMP_NAME}

echo "Mouting DMG file"
DEVICE=$(hdiutil attach -readwrite -noverify -noautoopen ${DMG_TMP_NAME} | \
                egrep '^/dev/' | sed 1q | awk '{print $1}')
echo "Adding Applications link"

ln -s /Applications "/Volumes/${VOLUME_NAME}/Applications"

echo "Customizing disk image"

echo '
	tell application "Finder"
		tell disk "'${VOLUME_NAME}'"
			open
			
			set theXOrigin to 50
			set theYOrigin to 50
			set theWidth to 500
			set theHeight to 300

            set theBottomRightX to (theXOrigin + theWidth)
			set theBottomRightY to (theYOrigin + theHeight)
			set dsStore to "/Volumes/'${VOLUME_NAME}'/.DS_STORE"

            tell container window
				set current view to icon view
				set toolbar visible to false
				set statusbar visible to false
				set the bounds to {theXOrigin, theYOrigin, theBottomRightX, theBottomRightY}
				set statusbar visible to false
				set position of every item to (theBottomRightX + 100, 100)
			end tell

            set opts to the icon view options of container window
			tell opts
				set icon size to 128
				set text size to 16
				set arrangement to not arranged
			end tell
            
            set position of item "'${APP_BUNDLE}'" to (20,20)
			
			set position of item "Applications" to (300,20)
            close
            open
            update without registering applications
			delay 1

            tell container window
				set statusbar visible to false
				set the bounds to {theXOrigin, theYOrigin, theBottomRightX - 10, theBottomRightY - 10}
			end tell

            update without registering applications

        end tell

        delay 1
		
		tell disk "'${VOLUME_NAME}'"
			tell container window
				set statusbar visible to false
				set the bounds to {theXOrigin, theYOrigin, theBottomRightX, theBottomRightY}
			end tell
			
			update without registering applications
		end tell

        --give the finder some time to write the .DS_Store file
		delay 3

        set waitTime to 0
		set ejectMe to false
		repeat while ejectMe is false
			delay 1
			set waitTime to waitTime + 1
			
			if (do shell script "[ -f " & dsStore & " ]; echo $?") = "0" then set ejectMe to true
		end repeat
		log "Waited " & waitTime & " seconds for .DS_STORE to be created."
	end tell
' | osascript

echo "Waiting a few seconds..."
sleep 5

echo "Fixing permissions"
chmod -Rf go-w "/Volumes/${VOLUME_NAME}" &> /dev/null || true

echo "Blessing"
bless --folder "/Volumes/${VOLUME_NAME}" --openfolder "/Volumes/${VOLUME_NAME}"

echo "Unmouting disk image"
hdiutil detach ${DEVICE}

echo "Compressing disk image..."
hdiutil convert "${DMG_TMP_NAME}" -format UDZO -imagekey zlib-level=9 -o "${DMG_NAME}"
rm -f "${DMG_TMP_NAME}"

echo "DMG disk image created."

popd
