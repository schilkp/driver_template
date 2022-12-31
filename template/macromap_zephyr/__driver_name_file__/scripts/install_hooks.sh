#!/bin/bash

mkdir -p $$(dirname $$0)/../.git/hooks
cp $$(dirname $$0)/pre-commit $$(dirname $$0)/../.git/hooks/pre-commit
