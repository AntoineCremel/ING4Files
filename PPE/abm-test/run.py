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

"""
fixed_params = {"width": 10,
				"height": 10}
variable_params = {"N": range(10, 500, 10)}

batch_run = BatchRunner(MoneyModel, variable_params, fixed_params,
						iterations=5, max_steps=100, model_reporters={"Gini": compute_gini})

batch_run.run_all()

run_data = batch_run.get_model_vars_dataframe()
plt.scatter(run_data.N, run_data.Gini)


agent_counts = np.zeros((model.grid.width, model.grid.height))
for cell in model.grid.coord_iter():
	cell_content, x, y = cell
	agent_count = len(cell_content)
	agent_counts[x][y] = agent_count

plt.imshow(agent_counts, interpolation = 'nearest')
plt.colorbar()

plt.show()
"""
