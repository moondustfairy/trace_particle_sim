energy = []
diff_flux_e = []
list_tuples = []
mean_energy = 0
with open("data/crdb_electron.GALPROP", "r") as f:
    lines = f.readlines()
    for line in lines[10:-37]:
        nums = [n for n in line.strip().split()]
        energy.append(float(nums[5])*10**3)
        diff_flux_e.append(float(nums[8]))
        mean_energy += float(nums[5]*10**3) * float(nums[8])
        list_tuples.append((float(nums[5])*10**3, float(nums[8])))
    f.close()

# sort by energy
list_tuples.sort()

f1 = open("diff_flux_electron.txt", "w")
for i in range(len(energy)):
    f1.write(str(list_tuples[i][0]) + " " + str(list_tuples[i][1]) + "\n")

f1.close()
print("Weighted mean energy for electrons: " + str(mean_energy))