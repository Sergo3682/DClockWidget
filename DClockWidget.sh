#!/bin/bash

args=$(head -n 1 config)
./app $args &
