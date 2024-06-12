import matplotlib.pyplot as plt
import numpy as np

def extract_data(data):
    
    time_list = data[:, 0]
    epsilon_xx_list = data[:, 1]
    sigma_xx_list = data[:, 7]
    sigma_xx_MPa_list = [sigma_xx*10**(-6) for sigma_xx in sigma_xx_list]
    ta_list = data[:, 20]
    
    return time_list, epsilon_xx_list, sigma_xx_MPa_list, ta_list
    

plt.close('all')
    
data = np.loadtxt('ekmc.res', skiprows=22)
time_list, epsilon_xx_list, sigma_xx_list, ta_list = extract_data(data)

print(sigma_xx_list[-1])


plt.figure()
# plt.plot(epsilon_xx_percent_ref_list, sigma_xx_ref_list, label='Reference')
plt.plot(epsilon_xx_list, sigma_xx_list)
plt.xlabel(r'Strain $\varepsilon\; \left[\mathrm{\%}\right]$')
plt.ylabel(r'Stress $\sigma\; \left[\mathrm{MPa}\right]$')
plt.grid()