import matplotlib.pyplot as plt
import sys
import numpy as np
import cv2
    

arq = open( sys.argv[1], "r" )
ambiente = open( sys.argv[2], "r" )
print sys.argv[2]
print sys.argv[3]
result = open( sys.argv[3], "r" )

lines = arq.readlines()
vet = np.array(([[ float(word) for word in  line.strip('\n').split(' ')]  for line in lines ] ))
plt.title("genetic algotithm evolution")
plt.grid()
plt.xlabel("number of generations")
plt.ylabel("fitness score")
xvalues = range( vet.shape[0] )
plt.plot( xvalues, vet[:,1], 'o-', color = 'g', label = 'means' )
plt.plot( xvalues, vet[:,0], 'o-', color = 'b', label = 'best' )
plt.plot( xvalues, vet[:,2], 'o-', color = 'r', label = 'std' )
plt.legend( loc = "best" )

canvas = np.ones((400, 400, 3)) * 255
preto = (0, 0, 0)
cor = (100, 0, 0)

circulos = result.readlines()
circulos = np.array([[ int( value ) for value in line.strip('\n').split(' ') ] for line in circulos ])*8
amb = ambiente.readlines()
amb = np.array( [[ value for value in line.strip('\n').split(' ') ] for line in amb ] )
amb = np.array([ [ int(value) for value in line ] for line in amb ])

print circulos

plt.show()
arq.close()
ambiente.close()

result.close()

for i in range(200):
    for j in range(200):
        if( amb[i][j] == 1 ):
            cv2.circle(canvas, (i*8, j*8,), 1, cor, -1 )

for i in range( circulos.shape[0] ):
    cv2.circle( canvas, ( circulos[i][0] ,circulos[i][1] ), circulos[i][2], preto)
cv2.imshow("Canvas", canvas)
cv2.waitKey(0)
