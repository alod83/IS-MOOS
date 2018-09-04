#!/bin/sh

valgrind --tool=memcheck --leak-check=full ../MOOSDB ../Mission.moos

