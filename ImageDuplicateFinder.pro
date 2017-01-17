TEMPLATE = subdirs
SUBDIRS += app \
        tests \
    image-duplicate-finder-lib

app.depends = image-duplicate-finder-lib
tests.depends = image-duplicate-finder-lib


