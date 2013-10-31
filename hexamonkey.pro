
TEMPLATE = subdirs


CONFIG += ordered

SUBDIRS = compiler \
          core \
          cli \
          gui

scripts.files = scripts/*.hm
unix: scripts.path = $$prefix.path/usr/share/hexamonkey/scripts
INSTALLS += scripts

resources.files = \
  models/hmcmodel.csv \
  models/mkvmodel.xml \
  compiler/hexacompiler \
  compiler/expcompiler \
  gui/logo.svg
unix: resources.path = $$prefix.path/usr/share/hexamonkey
INSTALLS += resources
