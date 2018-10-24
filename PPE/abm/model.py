#!usr/bin/env python3

'''Environment file

This file contains the definition of the environment.
It will contain a class inheriting from Model whcich will define
global variables such as the scheduler and other such variables '''

from mesa.model import Model


class World(Model):

	number = 0
