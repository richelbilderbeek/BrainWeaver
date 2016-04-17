#!/bin/bash
function clean {
  rm moc_*
  rm object_script*.*
  rm ui_*
  rm qrc_*
  rm *.gcov
  rm *.gcda
  rm *.gcno
  rm *.o
  rm *_plugin_import.cpp
  rm *.pro.user
  rm Makefile
  rm Makefile.Debug
  rm Makefile.Release
  rm boost_graph_tutorial_test
  rm boost_graph_tutorial
  rm exe_debug.txt
  rm exe_release.txt
  rm test_debug.txt
  rm test_release.txt
  rm -rf debug
  rm -rf release
  rm tmp*
}

clean
