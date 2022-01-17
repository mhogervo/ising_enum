import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

f_2_2 = 'run_2_2.txt'
f_2_3 = 'run_2_3.txt'
f_2_4 = 'run_2_4.txt'
f_2_5 = 'run_2_5.txt'
f_3_2 = 'run_3_2.txt'
f_3_3 = 'run_3_3.txt'
f_4_2 = 'run_4_2.txt'

d_2_2 = np.loadtxt(f_2_2, dtype = float)
d_2_3 = np.loadtxt(f_2_3, dtype = float)
d_2_4 = np.loadtxt(f_2_4, dtype = float)
d_2_5 = np.loadtxt(f_2_5, dtype = float)
d_3_2 = np.loadtxt(f_3_2, dtype = float)
d_3_3 = np.loadtxt(f_3_3, dtype = float)
d_4_2 = np.loadtxt(f_4_2, dtype = float)

tanhBetaList = d_2_2[:,0]

en_2_2 = d_2_2[:,2]
en_2_3 = d_2_3[:,2]
en_2_4 = d_2_4[:,2]
en_2_5 = d_2_5[:,2]
en_3_2 = d_3_2[:,2]
en_3_3 = d_3_3[:,2]
en_4_2 = d_4_2[:,2]

susc_2_2 = d_2_2[:,3]
susc_2_3 = d_2_3[:,3]
susc_2_4 = d_2_4[:,3]
susc_2_5 = d_2_5[:,3]
susc_3_2 = d_3_2[:,3]
susc_3_3 = d_3_3[:,3]
susc_4_2 = d_4_2[:,3]

dersusc_2_2 = d_2_2[:,4]
dersusc_2_3 = d_2_3[:,4]
dersusc_2_4 = d_2_4[:,4]
dersusc_2_5 = d_2_5[:,4]
dersusc_3_2 = d_3_2[:,4]
dersusc_3_3 = d_3_3[:,4]
dersusc_4_2 = d_4_2[:,4]

# fig, ax = plt.subplots()
# ax_2_2, = ax.plot(tanhBetaList, susc_2_2, label = '2^2')
# ax_2_3, = ax.plot(tanhBetaList, susc_2_3, label = '2^3')
# ax_2_4, = ax.plot(tanhBetaList, susc_2_4, label = '2^4')
# ax_2_5, = ax.plot(tanhBetaList, susc_2_5, label = '2^5')
# ax_3_2, = ax.plot(tanhBetaList, susc_3_2, label = '3^2')
# ax_3_3, = ax.plot(tanhBetaList, susc_3_3, label = '3^3')
# ax_4_2, = ax.plot(tanhBetaList, susc_4_2, label = '4^2')
# ax.legend(handles = [ax_2_2, ax_2_3, ax_2_4, ax_2_5, ax_3_2, ax_3_3, ax_4_2])
# plt.xlabel('tanh(beta)')
# plt.ylabel('susceptibility chi')
# plt.show()


# fig, ax = plt.subplots()
# ax_2_2, = ax.plot(tanhBetaList, dersusc_2_2, label = '2^2')
# ax_2_3, = ax.plot(tanhBetaList, dersusc_2_3, label = '2^3')
# ax_2_4, = ax.plot(tanhBetaList, dersusc_2_4, label = '2^4')
# ax_2_5, = ax.plot(tanhBetaList, dersusc_2_5, label = '2^5')
# ax_3_2, = ax.plot(tanhBetaList, dersusc_3_2, label = '3^2')
# ax_3_3, = ax.plot(tanhBetaList, dersusc_3_3, label = '3^3')
# ax_4_2, = ax.plot(tanhBetaList, dersusc_4_2, label = '4^2')
# ax.legend(handles = [ax_2_2, ax_2_3, ax_2_4, ax_2_5, ax_3_2, ax_3_3, ax_4_2])
# plt.xlabel('tanh(beta)')
# plt.ylabel('d chi/d beta')
# plt.show()


fig, ax = plt.subplots()
ax_2_2, = ax.plot(tanhBetaList, en_2_2, label = '2^2')
ax_2_3, = ax.plot(tanhBetaList, en_2_3, label = '2^3')
ax_2_4, = ax.plot(tanhBetaList, en_2_4, label = '2^4')
ax_2_5, = ax.plot(tanhBetaList, en_2_5, label = '2^5')
ax_3_2, = ax.plot(tanhBetaList, en_3_2, label = '3^2')
ax_3_3, = ax.plot(tanhBetaList, en_3_3, label = '3^3')
ax_4_2, = ax.plot(tanhBetaList, en_4_2, label = '4^2')
ax.legend(handles = [ax_2_2, ax_2_3, ax_2_4, ax_2_5, ax_3_2, ax_3_3, ax_4_2])
plt.xlabel('tanh(beta)')
plt.ylabel('energy')
plt.show()
