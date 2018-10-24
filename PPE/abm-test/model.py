import random

from mesa import Agent, Model
from mesa.time import RandomActivation
from mesa.space import MultiGrid

class MoneyAgent(Agent):
	""" An agent with fixed initial wealth"""
	def __init__(self, unique_id, model):
		super().__init__(unique_id, model)
		self.wealth = 1

	def move(self):
		possible_steps = self.model.grid.get_neightborhood(
			self.pos,
			moore = True;
			include_center = False)
		new_position = random.choice(possible_steps)
		self.model.grid.move_agent(self, new_position)

	def give_money(self):
		cellmates = self.model.grid.get_cell_list_contents([self.pos])
		if len(cellmates) > 1:
			other = random.choice(cellmates)
			other.wealth += 1
			self.wealth -= 1

	def step(self):
		# The agents steps will go here
		self.move()
		if self.wealth > 0:
			self.give_money()

class MoneyModel(Model):
	""" A model with some number of agents"""
	def __init__(self, N, width, height):
		self.num_agents = N
		self.grid = MultiGrid(width, height, True)
		self.schedule = RandomActivation(self)

		# Create N agents
		for i in range (self.num_agents):
			a = MoneyAgent(i, self)
			self.schedule.add(a)

			# Add the agents to the grid
			x = random.randrange(self.grid.width)
			y = random.randrange(self.grid.height)
			self.grid.place_agent(a, (x, y))

	""" Define the scheduler for the model"""
	def step(self):
		self.schedule.step()
		# At the end of each steap, print the wealth of each agent
		for a in self.schedule.agents:
			print(a.unique_id, " has ", a.wealth, " wealth")
