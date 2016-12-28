git log --format=%aN |sort -u |while read name; do echo "`git log --author=\"$name\" --pretty=oneline |wc -l` $name"; done
