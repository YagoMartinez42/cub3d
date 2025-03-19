import math

crds = [2.001, 3.1]

d_crds = [2.345, 3.212]

step_x = d_crds[0] - crds[0]
step_y = d_crds[1] - crds[1]
if (step_x <= step_y):
	step = step_y
else:
	step = step_x

print(step)
print(step_x/step)
print(step_y/step)
step_x = step_x/step
step_y = step_y/step
print(crds, d_crds)
while (step >= 0.1):
	crds[0] = crds[0] + (step_x * 0.1)
	crds[1] = crds[1] + (step_y * 0.1)
	step = step -0.1
	print(crds)
crds[0] = crds[0] + (step_x * step*0.999)
crds[1] = crds[1] + (step_y * step*0.999)
print(crds)
