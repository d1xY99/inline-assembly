#include <stdio.h>
#include <x86intrin.h>

void get_cpuid(unsigned int idx, unsigned int cpuid[4]) {
    asm volatile (
        "movl %[idx], %%eax\n\t"   // Move idx to eax
        "xorl %%ecx, %%ecx\n\t"    // Zero out ecx
        "cpuid\n\t"
        "movl %%eax, (%[cpuid])\n\t"
        "movl %%ebx, 4(%[cpuid])\n\t"
        "movl %%ecx, 8(%[cpuid])\n\t"
        "movl %%edx, 12(%[cpuid])\n\t"
        : // No output
        : [idx] "r" (idx), [cpuid] "r" (cpuid)
        : "eax", "ebx", "ecx", "edx"
    );
}

int main()
{
	char vendor[0x20];
	unsigned int data_[100];
	unsigned int extdata_[100];
	unsigned int cpuid[4];
	unsigned int f_1_ECX_;
	unsigned int f_1_EDX_;
	unsigned int f_7_EBX_;
	unsigned int f_7_ECX_;
	unsigned int f_7_EDX_;
	unsigned int f_81_ECX_;
	unsigned int f_81_EDX_;
	get_cpuid(0,cpuid);
	
	int nIds_ = cpuid[0];
	int i;
	for (i = 0;i <= nIds_;i++)
	{
		get_cpuid(i,cpuid);
		data_[i*4] = cpuid[0];
		data_[i*4 + 1] = cpuid[1];
		data_[i*4 + 2] = cpuid[2];
		data_[i*4 + 3] = cpuid[3];
	}

	// load bitset with flags for function 0x00000001
	if (nIds_ >= 1)
	{
		f_1_ECX_ = data_[6];
		f_1_EDX_ = data_[7];
	}

	// load bitset with flags for function 0x00000007
	if (nIds_ >= 7)
	{
		f_7_EBX_ = data_[29];
		f_7_ECX_ = data_[30];
		f_7_EDX_ = data_[31];
	}

	memset(vendor, 0, sizeof(vendor));
	memcpy(vendor,&data_[1],4);
	memcpy(vendor+4,&data_[3],4);
	memcpy(vendor+8,&data_[2],4);

	printf("Manufacturer id: %s\n",vendor);

	get_cpuid(0x80000000, cpuid);
	int nExIds_ = cpuid[0];

	char brand[0x40];
	memset(brand, 0, sizeof(brand));

	for (i = 0x80000000; i <= nExIds_; ++i)
	{
		get_cpuid(i,cpuid);
		extdata_[(i - 0x80000000)*4] = cpuid[0];
		extdata_[(i - 0x80000000)*4 + 1] = cpuid[1];
		extdata_[(i - 0x80000000)*4 + 2] = cpuid[2];
		extdata_[(i - 0x80000000)*4 + 3] = cpuid[3];
	}
	// load bitset with flags for function 0x80000001
	if (nExIds_ >= 0x80000001)
	{
		f_81_ECX_ = extdata_[6];
		f_81_EDX_ = extdata_[7];
	}
	// Interpret CPU brand string if reported
	if (nExIds_ >= 0x80000004)
	{
		memcpy(brand, &extdata_[8], 16);
		memcpy(brand + 16, &extdata_[12], 16);
		memcpy(brand + 32, &extdata_[16], 16);
	}
	printf("Processor brand string: %s\n",brand);

	printf("vme: %u, apic: %u, acpi: %u, sse: %u, sdbg: %u, mpx: %u, sha: %u, serialize: %u\n", 
		f_1_EDX_&0x00000002 ? 1:0,
		f_1_EDX_&0x00000020 ? 1:0,
		f_1_EDX_&0x00400000 ? 1:0,
		f_1_EDX_&0x02000000 ? 1:0,
		f_1_ECX_&0x00000800 ? 1:0,
		f_7_EBX_&0x00004000 ? 1:0,
		f_7_EBX_&0x20000000 ? 1:0,
		f_7_EDX_&0x00004000 ? 1:0);

}


