
class Bank:
    def __init__(self):
        # All of these are integers
        self.dette = 0
        self.portfolio = 0
        self.prets = 0
        self.deposit = 0
        self.liquidity = 0

    def update(self):
        '''Set the banks variables

        Set the banks liquidity so that it stays true to
        the value of the other variables
        '''
        self.liquidity = self.dette + self.deposit -\
            (self.portfolio + self.prets)

    def create(self, new_dette, new_deposit, new_portfolio, new_pret):
        ''' Fonction pour générer une nouvelle instance de la classe
        Bank, en incrémentant chaque membre de la valeur passée en
        paramètres'''
        self.dette = self.dette + new_dette
        self.deposit = self.deposit + new_deposit
        self.portfolio = new_portfolio
        self.prets = new_pret
        self.update()

    def emprunte(self, preteur, somme):
        ''' Méthode pour faire emprunter à la banque self
        une somme à un preteur. Ce preteur devrait être un
        objet de classe banque également'''
        # Mettre à jour les valeurs de la banque self
        self.dette = self.dette + somme
        self.update()

        # Mettre à jour les valeurs du préteur
        preteur.prets = preteur.prets + somme
        preteur.update()

    def show(self):
        '''
        Function for printing out the state of the bank self
        '''
        print('Dette : ', self.dette, '\nDepots : ',
              self.deposit, '\nPortfolio : ', self.portfolio,
              '\nPrets : ', self.prets, '\nLiquidites : ', self.liquidity,
              '\nBalance=',
              (self.dette + self.deposit) -
              (self.portfolio + self.prets + self.liquidity),
              '\n\n')


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
        self.wealth = self.wagepaid * self.labor +\
            self.deporate * self.deposit + self.wealth

    def borrow(self, bank, somme):
        self.debt = self.debt + somme
        self.deposit = self.deposit + somme
        bank.liquidity = bank.liquidity - somme
        bank.prets = bank.prets + somme

    def show(self):
        print(self.debt, self.wealth, self.deposit)


a = Bank()
a.create(350, 200, 250, 200)
bnp = Bank()
bnp.create(300, 270, 215, 255)

a.show()
bnp.show()

print('banks cross loans')
a.emprunte(bnp, 75)
bnp.emprunte(a, 95)
a.show()
bnp.show()

john = Household()
print('john')
john.borrow(bnp, 63)
john.show()
print('after borrowing')
bnp.show()
