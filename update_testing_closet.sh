#!/usr/bin/bash -e

BRANCH=${1:-testing-closet}

git fetch
git checkout -f $BRANCH
git reset --hard origin/$BRANCH
git submodule update
reboot || sudo reboot
