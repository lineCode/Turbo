a = Account(100)
b = Account:new(30)

print('a =', a)
print('b =', b)
print('metatable =', getmetatable(a))
print('Account =', Account)
table.foreach(Account, print)

a:show() a:deposit(50.30) a:show() a:withdraw(25.10) a:show()

