from model import *
import matplotlib.pyplot as plt
import numpy as np

model = MoneyModel(50, 10, 10)
for i in range(100):
	model.step()

gini = model.datacollector.get_model_vars_dataframe()
gini.plot()
agent_wealth = model.datacollector.get_agent_vars_dataframe()
agent_wealth.head()

"""
agent_counts = np.zeros((model.grid.width, model.grid.height))
for cell in model.grid.coord_iter():
	cell_content, x, y = cell
	agent_count = len(cell_content)
	agent_counts[x][y] = agent_count

plt.imshow(agent_counts, interpolation = 'nearest')
plt.colorbar()

plt.show()
"""
