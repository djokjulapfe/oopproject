import string
from random import *

nameSize = 3
varNum = 10
exprNum = 30
exprSize = 10
maxNum = 10
maxRes = 1e9


def rand_name():
	all_char = string.ascii_letters
	password = "".join(choice(all_char) for x in range(nameSize))
	return password


def random_token(vars):
	if randint(1, 2) == 1:
		return choice(list(vars.keys()))
	return str(randint(1, maxNum))


def random_op():
	return choice(['+', '*'])


def rnd_expr(vars):
	expr = random_token(vars)
	if expr in vars:
		evaluable = 'vars["{}"]'.format(expr)
	else:
		evaluable = expr
	for i in range(exprSize):
		rop = random_op()
		rtk = random_token(vars)
		expr = '{} {} {}'.format(expr, rop, rtk)
		if rtk in vars:
			evaluable = '{} {} {}'.format(evaluable, rop, 'vars["{}"]'.format(rtk))
		else:
			evaluable = '{} {} {}'.format(evaluable, rop, rtk)

	return expr, evaluable


def createTest(testName):
	with open(testName + '.dbp', 'w') as out_file:
		vars = set()
		while len(vars) < varNum + exprNum:
			vars = vars | {rand_name()}

		vars = list(vars)
		expr_names = vars[varNum:]
		vars = vars[:varNum]

		# vars[varname] is it's value
		vars = {var: randint(1, maxNum) for var in vars}

		for var, val in vars.items():
			out_file.write('{} = {}\n'.format(var, val))

		for i in range(exprNum):
			expr, evaluable = rnd_expr(vars)
			while (eval(evaluable) > maxRes):
				expr, evaluable = rnd_expr(vars)
			out_file.write('{} = {}{}'.format(expr_names[0], expr, '\n' if i != exprNum-1 else ''))
			vars[expr_names[0]] = eval(evaluable)
			expr_names = expr_names[1:]

		results = []
		for var, val in vars.items():
			results += ['{} = {}'.format(var, val)]
		results.sort()

		with open(testName + '.txt', 'w') as out_result:
			for v in results:
				out_result.write(v + '\n')

for idx in range(10, 100):
	print(100 * (idx - 10) // 89)
	createTest("test" + str(idx))
