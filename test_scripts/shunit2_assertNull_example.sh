#!/bin/bash

function create_null()
{
  echo ""
}

test_create_null()
{
  assertNull `create_null`
}

# load shunit2
. ../../shunit2/source/2.1/src/shunit2