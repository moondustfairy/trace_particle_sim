energy = []
diff_flux_e = []

with open("data/crdb_electron.GALPROP", "r") as f:
    lines = f.readlines()
    for line in lines[10:-37]:
        nums = [n for n in line.strip().split()]
        energy.append(float(nums[5]))
        diff_flux_e.append(float(nums[8]))
    f.close()

f1 = open("diff_flux_electron.txt", "w")
for i in range(len(energy)):
    f1.write(str(energy[i]) + " " + str(diff_flux_e[i]) + "\n")

f1.close()