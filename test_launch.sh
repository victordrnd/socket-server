#!/bin/bash
(sleep 1 && timeout 3 ./output/client)&
timeout 5 ./output/server

