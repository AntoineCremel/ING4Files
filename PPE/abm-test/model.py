import random

from mesa import Agent, Model
from mesa.time import RandomActivation
from mesa.space import MultiGrid
from mesa.datacollection import DataCollector

class MoneyAgent(Agent):
	""" An agent with fixed initial wealth"""
	def __init__(self, unique_id, model):
		super().__init__(unique_id, model)
		self.wealth = 1

	def move(self):
		possible_steps = self.model.grid.get_neighborhood(
			self.pos,
			moore = True,
			include_center = False)
		new_position = random.choice(possible_steps)
		self.model.grid.move_agent(self, new_position)

	def give_money(self):
		cellmates = self.model.grid.\
			get_cell_list_contents([self.pos])
		if len(cellmates) > 1:
			other = random.choice(cellmates)
			other.wealth += 1
			self.wealth -= 1

	def step(self):
		# The agents steps will go here
		self.move()
		if self.wealth > 0:
			self.give_money()

def compute_gini(model):
	agent_wealths =\
		[agent.wealth for agent in model.schedule.agents]
	x = sorted(agent_wealths)
	N = model.num_agents
	B = sum(xi * (N-i) for i, xi in enumerate(x)) / (N*sum(x))
	return (1 + (1/N) - 2 * B)

class MoneyModel(Model):
	""" A model with some number of agents"""
	def __init__(self, N, width, height):
		self.num_agents = N
		self.grid = MultiGrid(width, height, True)
		self.schedule = RandomActivation(self)
		# Attribute for batch runs
		self.running = True

		# Create N agents
		for i in range (self.num_agents):
			a = MoneyAgent(i, self)
			self.schedule.add(a)

			# Add the agents to the grid
			x = random.randrange(self.grid.width)
			y = random.randrange(self.grid.height)
			self.grid.place_agent(a, (x, y))

		# Create the data collector
		self.datacollector = DataCollector(
			model_reporters = {"Gini": compute_gini}, 
			agent_reporters = {"Wealth": "wealth"})

	""" Define the scheduler for the model"""
	def step(self):
		self.datacollector.collect(self)
		self.schedule.step()
