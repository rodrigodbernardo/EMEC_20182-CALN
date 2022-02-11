# Implementar algoritmo para calcular d pelo método de Newton com FL

# Método de Newton com FL

import math

#DEFINICAO DA FUNCAO

def f(d,a3,a2):
  return a3*(d**3) - 9*a2*d + 3

#DEFINICAO DA DERIVADA

def df(d,a3,a2):
  return 3*a3*(d**2) - 9*a2


iterations = 100 
target = 0.3376089559658
d0_ = 0.5

l, a3, a2, e = map(float, input('Digite os valores de lambda, a3, a2 e precisão, separados por virgula: ').split(','))
iteration = 0

d0 = d0_

print("i\td(i)\t\tf(i)\t\tf'(i)\t\te(i)\n"+75*'-')

deriv_d1 = df(d0,a3,a2)   # Faz essa derivada só para a primeira interação

while iteration <= iterations:
  print('{}\t{:.6f}\t{:.6f}\t{:.6f}\t{:.6f}'.format(iteration,d0,f(d0,a3,a2),df(d0,a3,a2),abs(d0-target)))

  if(abs(d0-target) < e):
    print('\nPrecisão atingida. Encerrando loop..')
    break

  func  = f(d0,a3,a2)
  deriv_d0 = df(d0,a3,a2)

  if (deriv_d1 > l):      #se a derivada do D atual for menor que o lambda, usa a derivada do D anterior na formula
    fl = deriv_d1
  else:
    fl = deriv_d0

  d1 = d0 - func / fl     #FORMULA DO MET DE NEWTON com FL

  deriv_d1 = df(d1,a3,a2) #calcula a derivada de D1, preparando para a proxima iteração
  d0 = d1                 #d0 recebe o valor atual de d1, preparando para a proxima iteração

  iteration += 1
  
print('\n\n'+75*'*')
print('Iterações realizadas: {}\n'.format(iteration))

print('Raiz desejada:\t{:.6f}'.format(target))
print('Raiz obtida:\t{:.6f}'.format(d0))

print('\nErro máximo:\t{:.6f}'.format(e))
print('Erro obtido:\t{:.6f}'.format(d0-target))