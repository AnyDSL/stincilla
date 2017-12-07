# Interrupt service routine for : Ctrl + C
# Beware the sleep at the end of the loop
my $exitflag = 0;
$SIG{INT} = sub { $exitflag=1; };

#@list = (g1cap, g1fac);
@list = (g1cap_mirror, g1fac_mirror, g1cap_nobh, g1fac_nobh, g1cap, g1fac, 
         g8cap, g8fac, g8cap_mirror, g8fac_mirror, g8cap_nobh, g8fac_nobh,
         g16cap, g16fac, g16cap_mirror, g16fac_mirror, g16cap_nobh, g16fac_nobh,
         g32cap, g32fac, g32cap_mirror, g32fac_mirror, g32cap_nobh, g32fac_nobh);

my $compile = 0; # 0: emulation, 1: compilation
if ($compile == 0) {
    #emulation
    $target_path = "uchar_em";
} else {
    #compilation
    $target_path = "uchar";
}
mkdir -p $target_path;

foreach $design  (@list) {
    $design_path      = $target_path."/".$design;
    $design_path_temp = $target_path."/temp_".$design;
    if (-d $design_path) {
        print("$design_path exist\n"); 
    } elsif (-d $design_path_temp) {
        print("$design_path_temp exist\n"); 
    } else {
        system("mkdir -p $design_path_temp");
        $binary_file = $design."_host";
        $kernel_file = $design.".cl";
        $clang_file  = $design.".ll";
        $aocl_file   = $design.".aocx";
        print("$design: \n");
        print("Clear old files\n");
        system("rm -r $design*");
        print("make: \n");
        system("time make $design");
        print("rename host file");
        system("mv ${design} ${binary_file}");
        if ($compile == 0) {
            ## emulation
            print("emulate kernel: \n");
            system("aoc --report -march=emulator $kernel_file -o $aocl_file");
            print("run emulation: \n");
            my $emulation_log_file = $design.".log";
            system("CL_CONTEXT_EMULATOR_DEVICE_ALTERA=1 ./$binary_file | tee $emulation_log_file");
            system("mkdir -p $design_path");
            system("mv $emulation_log_file $design_path/");
        } else {
        ## compile
            print("compile kernel: \n");
            system("aoc --report $kernel_file -o $aocl_file");
            #Archieve files
            if(-e $aocl_file) {
                print("mv $design $aocl_file $kernel_file $binary_file $design_path");
                system("mkdir -p $design_path");
                system("mv $aocl_file $kernel_file $binary_file $clang_file $design_path");
                system("mkdir $design_path/$design");
                system("mv $design/reports $design/*.log $design/acl_quartus_report.txt $design_path/$design");
            }
        }
        system("rm -r $design_path_temp");
    }
    # exit if I ask
    sleep(1);
    if ($exitflag == 1) {
        print("\n\nYou asked me to leave the job unfinished!\n\n");
        last;
    }
}
