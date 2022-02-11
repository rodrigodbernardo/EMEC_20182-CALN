# Implementar método numerico para achar a derivada de f(d) e refazer o item a

# Método de Newton com aproximação da derivada

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

d = [0,d0_]
fn = [0,0]
dfn = [0,0]

print("i\td(i)\t\tf(i)\t\tf'(i)\t\te(i)\n"+75*'-')
while iteration <= iterations:
  fn.append(f(d[-1],a3,a2))
  #dfn.append(df(d[-1],a3,a2))
  dfn.append((fn[-1]-fn[-2])/(d[-1]-d[-2]))   # <---- Aproximação da derivada

  #d.pop(0)
  fn.pop(0)
  dfn.pop(0)
  
  #print(d)
  print('{}\t{:.6f}\t{:.6f}\t{:.6f}\t{:.6f}'.format(iteration,d[-1],fn[-1],dfn[-1],abs(d[-1]-target)))

  if(abs(d[-1]-target) < e):
    print('\nPrecisão atingida. Encerrando loop..')
    break

  d.append(d[-1] - (fn[-1] / dfn[-1]))
  
  d.pop(0)

  iteration += 1
  
print('\n\n'+75*'*')
print('Iterações realizadas: {}\n'.format(iteration))

print('Raiz desejada:\t{:.6f}'.format(target))
print('Raiz obtida:\t{:.6f}'.format(d[-1]))

print('\nErro máximo:\t{:.6f}'.format(e))
print('Erro obtido:\t{:.6f}'.format(d[-1]-target))
print(d)