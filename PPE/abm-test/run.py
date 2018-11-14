from model import *
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
# Necessary for batch runs
from mesa.batchrunner import BatchRunner
# For real time visualisation
from server import server
server.port = 8521 # Default port for this shiet
server.launch()

