energy = []
diff_flux_h = []
diff_flux_he = []
mean_h = 0
mean_he = 0

with open("data/spenvis_gcf_h_he.txt", "r") as f:
	lines = f.readlines()
	for line in lines[89:-1]:
		nums = [n for n in line.strip().split(",")]
		energy.append(float(nums[0]))
		diff_flux_h.append(float(nums[3]))
		diff_flux_he.append(float(nums[4]))
		mean_h += float(nums[0]) * float(nums[3])
		mean_he += float(nums[0]) * float(nums[4])
	f.close()

f1 = open("diff_flux_h.txt", "w")
f2 = open("diff_flux_he.txt", "w")

for i in range(len(energy)):
	f1.write(str(energy[i]) + " " + str(diff_flux_h[i]) + "\n")
	f2.write(str(energy[i]) + " " + str(diff_flux_he[i]) + "\n")

f1.close()
f2.close()

print("Weighted mean energy for H: " + str(mean_h))
print("Weighted mean energy for He: " + str(mean_he))


