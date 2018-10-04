# import numpy as np
class Bank:
    def __init__(self):
     self.dette =0
     self.portfolio =0
     self.prets =0
     self.deposit = 0
     self.liquidity = 0

    def create( self, aaa, bbb , ccc, ddd):
        self.dette = self.dette + aaa
        self.deposit = self.deposit + bbb
        self.portfolio = ccc
        self.prets = ddd
        self.liquidity = self.dette + self.deposit - (self.portfolio+self.prets)

    def emprunte (self, preteur, somme):
        self.dette = self.dette + somme
        self.liquidity = self.liquidity + somme
        preteur.liquidity = preteur.liquidity - somme
        preteur.prets = preteur.prets + somme
    def controle (self):
        print(self.dette, self.deposit, self.portfolio, self.prets, self.liquidity, 'balance=',(self.dette + self.deposit) - (self.portfolio + self.prets + self.liquidity))

class Household:
    labormax = 4000
    wealth = 0
    debt = 0
    labor = 0
    wagepaid = 0
    bank = ""
    deporate = 0
    deposit = 0

    def __init__(self):
        self.wealth = self.wagepaid*self.labor + self.deporate*self.deposit + self.wealth

    def borrow (self, bank, somme):
        self.debt = self.debt + somme
        self.deposit = self.deposit + somme
        bank.liquidity = bank.liquidity - somme
        bank.prets = bank.prets + somme

    def controle (self):
        print(self.debt, self.wealth, self.deposit)
        # print((self.dette))

a = Bank()
a.create(350,200,250,200)
bnp=Bank()
bnp.create(300,270,215,255)

a.controle()
bnp.controle()

print('banks cross loans')
a.emprunte (bnp, 75)
bnp.emprunte (a, 95)
a.controle()
bnp.controle()

john=Household()
print('john')
john.borrow(bnp,63)
john.controle()
print('after borrowing')
bnp.controle()