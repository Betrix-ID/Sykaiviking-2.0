#!/system/bin/sh
# Checking ID shell
if [ "$(id -u)" -ne 2000 ]; then
    echo "[ Error |@UnixeID(Yeye)]"
    exit 1
fi
# Smart Notification
shell() {
    sor="$1"
    cmd notification post -S bigtext -t '♨️ Sykaiviking' 'Tag' "$sor" > /dev/null 2>&1
}
# Style display Terminal
    echo
    echo "     ☆================================☆"
    echo
    echo "       ~ Description. Sykaiviking.... "
    echo
    echo "       - Author                 :  @UnixeID"
    echo "       - Point                    :  2.0 [ Oulet ]"
    echo "       - Release               :  18 - Mar - 2025"
    echo "       - Name Shell         :  Sykaiviking"
    echo
    echo "    |_______________________________________|"
    echo "    \______________________________________/"
    echo
    echo "   Priority Renderer Optimization. "
    sleep 2
    echo
    echo
     rm -rf /data/local/tmp/*
     cp /sdcard/Ques/skia /data/local/tmp 
     chmod +x /data/local/tmp/skia
       if [ "$1" = "-L" ]; then
        shell "Wait To Apply Sykaiviking Layersl Min 1-3"
        /data/local/tmp/skia -L
    elif [ "$1" = "-N" ]; then
         shell "Wait To Apply Sykaiviking Don't Layers Min 1-3"
        /data/local/tmp/skia -N
    elif [ "$1" = "-h" ]; then
       /data/local/tmp/skia -h
    elif [ "$1" = "--help" ]; then
       /data/local/tmp/skia --help
    else
        printf "Usage VelocityHz [-L|-N|-h]\n"
    fi
    