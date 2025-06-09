import numpy as np
import matplotlib.pyplot as plt

# Parameter aliran
radius = 0.05       # 5 cm
length = 10.0       # 10 m
viscosity = 0.001   # Air pada 20°C
density = 1000.0    # Air
pressure_drop_laminar = 1000.0  # 1 kPa
pressure_drop_turbulent = 10000.0  # 10 kPa
n_points = 100

# menghitung profil kecepatan laminar
def calculate_laminar_flow(radius, length, viscosity, pressure_drop, n_points):
    dr = radius / (n_points - 1)
    factor = pressure_drop / (4 * viscosity * length)
    velocity = np.zeros(n_points)
    
    for i in range(n_points):
        r = i * dr
        velocity[i] = factor * (radius**2 - r**2)
    return velocity

# menghitung profil kecepatan turbulen
def calculate_turbulent_flow(radius, length, viscosity, pressure_drop, density, n_points):
    dr = radius / (n_points - 1)
    u_star = np.sqrt(pressure_drop * radius / (2 * density * length))
    kappa = 0.41  # Konstanta von Kármán
    B = 5.5       # Konstanta log-law
    velocity = np.zeros(n_points)
    
    for i in range(n_points):
        r = radius - i * dr
        if r < 1e-6: r = 1e-6  # Hindari division by zero
        
        # Hukum dinding logaritmik
        y_plus = r * u_star * density / viscosity
        velocity[i] = u_star * (1/kappa * np.log(y_plus) + B)
    return velocity

# Hitung aliran laminar
velocity_laminar = calculate_laminar_flow(radius, length, viscosity, pressure_drop_laminar, n_points)

# Hitung aliran turbulen
velocity_turbulent = calculate_turbulent_flow(radius, length, viscosity, pressure_drop_turbulent, density, n_points)

r_values = np.linspace(0, radius, n_points)

plt.figure(figsize=(10, 6))

plt.plot(r_values, velocity_laminar, label="Aliran Laminar", color='blue')

plt.plot(r_values, velocity_turbulent, label="Aliran Turbulen", color='red')

plt.title("Profil Kecepatan Aliran Laminar dan Turbulen dalam Pipa")
plt.xlabel("Jari-jari Pipa (m)")
plt.ylabel("Kecepatan (m/s)")
plt.legend()
plt.grid(True)

plt.show()
