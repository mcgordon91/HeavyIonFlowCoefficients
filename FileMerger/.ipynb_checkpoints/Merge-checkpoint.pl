#!/usr/bin/perl

use strict;
use warnings;
use Getopt::Long qw(GetOptions);
use Getopt::Long qw(HelpMessage);
use Cwd qw(abs_path);
use Pod::Usage;

=pod

=head1 NAME

Merge_ForMichael - Handy script for merging ROOT files from condor jobs generated from *MakeJob.pl*

=head1 SYNOPSIS

Merge.pl [option] [value] ...

  --dir1, -d, -d1    (requried) directory where root files are
  --dir2, -d2        (Don't use; hacked out) Second directory to compare
  --filter, -f       Name of file to match (search pattern will be filter_\d{8}_(?:raw_)?\d{7}.root)
  --nfiles, -n       Number of files to merge at once with hadd (no-op with -r)
  --outname, -o      Name of final output which will be [outname].root (default is "All")
  --runnum, -r       (Don't use; hacked out) Flag to indicate only files with matching runnumber should be merged; no overall merge performed
  --test, -t         Test only checks directories and arguments; does not merge. Use with verbose to get a listing
  --verbose, -v      Set the printout level (default is 1)
  --help, -h         Print this help

=head1 VERSION

2.0

=head1 PURPOSE

Merge output ROOT output files following some filter

=head2 DESCRIPTION

This program will merge the output ROOT files that match the "filter" argument

To use specify the job output folder where the ROOT files are located with the -d option. Specify what file names to look for with the -f option. Specify any other options as needed which can be checked with -h.

=cut

=begin comment
LOG
@[December 20, 2024]
> Copied from 'Merge.pl' and modified (hacked out) the runnmuber and directory 2 features. Filter argument will do regex match for provided argument 
=cut

my $DEBUG = 0;                           #Debug mode for printing only
#my $LOC = $ENV{'PWD'};
#my $DIR1 = "$LOC/DB414CE/Output";
#my $DIR2 = "$LOC/B8ACDD1/Output";

#my $DIR1 = "$LOC/028EB68/Output";
#my $DIR2 = "$LOC/124FDD3/Output";

#my $DIR1 = "$ENV{'HOME'}/pwg_disk/TestNewWff/DB414CE/Output";$ENV{'HOME'}/pwg_disk/TestNewWff/DB414CE/Output";
#my $DIR2 = "$ENV{'HOME'}/pwg_disk/TestNewWff/35E5751/Output";$ENV{'HOME'}/pwg_disk/TestNewWff/35E5751/Output";

#Here is the setup to check if the submit option was given
#my $LOC = $ENV{'PWD'};
my $DIR1;          #Main/First directory to merge
my $DIR2;          #Second directory to merge
my $FILTER = "HistogramFirstPassNormal";   #Name of input file (assumes files end in _runnumber_iteration.root)
my $NAME = "All";  #Name of final output file 
my $TEST;          #Boolean test mode to check what program will do without doing it
my $NFILES = 50;   #Number of files to merge at once
my $RUNNUM = 0;    #Option to merge files with same runnumber together. Only merges same runnumbers does not do overall merge
my $VERBOSE = 1;

GetOptions(
    'dir1|d|d1=s' => \$DIR1,
    'dir2|d2=s'   => \$DIR2,
    'filter|f=s'  => \$FILTER,
    'nfiles|n=i'  => \$NFILES,
    'outname|o=s' => \$NAME,
    'runnum|r'    => \$RUNNUM,
    'verbose|v=i' => \$VERBOSE,
    'test|t'      => \$TEST,
    'help|h'      => sub { HelpMessage(0) }
    ) or HelpMessage(1);


if( $NAME =~ m/Merge\d+/ ){ print "Error:outname cannot be 'Merge' followed by digits\n"; HelpMessage(0); }
if( $FILTER eq "" ){
    print "WARNING:No filter specified on file name\n";
    print "Please Specify Filter (Q/q to quit)?:";
    my $input = <STDIN>;
    chomp $input;
    if( $input eq "Q" || $input eq "q" || $input eq "" ){ print "Quitting\n"; HelpMessage(0); }
    else{ $FILTER = $input; }
}

if( ! $DIR1 ){ print "Error:No directory 1 given\n"; HelpMessage(0); }
my $char = chop $DIR1; #Get last character of DIR1
while( $char eq "/" ){$char = chop $DIR1;} #Remove all '/'
$DIR1 = $DIR1.$char;     #Append removed character which was not a '/'
$DIR1 = abs_path($DIR1); #Get absolute path
if( ! -d $DIR1 ){ die "'$DIR1' is not a directory '$!'"; }
if( $VERBOSE>=2 ){ print "Dir1:$DIR1\n"; }

my $numfiles = 0;
my $mergefiles1 = "";
my $finalmergefiles1 = "";
my %RunnumMerge;

if( ! $DIR2 ){ print "Warning:No directory 2 given merging only $DIR1\n"; }
else{
    $char = chop $DIR2; #Get last character of DIR2
    while( $char eq "/" ){$char = chop $DIR2;} #Remove all '/'
    $DIR2 = $DIR2.$char;     #Append removed character which was not a '/'
    $DIR2 = abs_path($DIR2); #Get absolute path
    if( ! -d $DIR2 ){ die "'$DIR2' is not a directory '$!'"; }
    if( $VERBOSE>=2 ){ print "Dir2:$DIR2\n"; }
}

my %Compare;

opendir my $dh1, $DIR1 or die "Could not open '$DIR1' for reading '$!'";

#if( $TEST && ! $DIR2 ){ exit(0); }

if( $VERBOSE>=1 ){ print "Reading $DIR1\n"; }
while( my $mudstfile = readdir $dh1 ){
    #@[July 30, 2024] > The (?:raw_) is optional group matching syntax, may need testing. Discovered when asking Google's Gemini how to match exact strings
    if( $mudstfile =~ m/${FILTER}/ ){
	my $runnum = "00000000";
	my $iternum = "0000000";
	if( $VERBOSE>=3 ){print " - |runnum:$runnum|iternum:$iternum|$mudstfile\n"; }
	#my $iternum = $mudstfile;
	#print "B: $iternum\n";
	#$iternum =~ s/${FILTER}_//;
	#$iternum =~ s/.root//;
	#print "A: $iternum\n";
	$Compare{$iternum} = 1; #1 (true) since it is in DIR1
	if( ! $DIR2 ){
	    if( $RUNNUM ){
		if( ! $RunnumMerge{$runnum} ){ $RunnumMerge{$runnum} = "$DIR1/$mudstfile"; $numfiles++; }
		else{ $RunnumMerge{$runnum} = $RunnumMerge{$runnum} . " $DIR1/$mudstfile"; $numfiles++; }
	    }
	    else{
		$mergefiles1 = $mergefiles1." $DIR1/$mudstfile";
		$numfiles++;
		if( $numfiles % $NFILES==0 ){
		    #print "hadd StFcsPi0invariantmass$numfiles.root$mergefiles\n";
		    #print "$numfiles\n";
		    $finalmergefiles1 = $finalmergefiles1 . " $DIR1/Merge$numfiles.root";
		    if( !$TEST ){ system( "hadd -f $DIR1/Merge$numfiles.root$mergefiles1" ); }# or die "Unable to hadd: $!";
		    $mergefiles1 = "";
		}
	    }
	}
    }
}

closedir $dh1;

if( $RUNNUM ){
    my $nruns = 0;
    for my $runnum ( keys %RunnumMerge ){
	print "Merging all runs with run number:$runnum\n";
	my @runnumfiles = split( / /, $RunnumMerge{$runnum} );
	my $nummergefiles1 = 0;
	if( $TEST || $VERBOSE>=2 ){
	    print( "Total files for run $runnum = ", scalar @runnumfiles, "\n");
	    foreach my $file ( @runnumfiles ){
		$nummergefiles1++;
		print( " ${nummergefiles1}. $file\n" );
	    }
	}
	if( !$TEST ){
	    my $mergefiles1 = "";
	    my $finalmergefiles1 = "";
	    $nummergefiles1 = 0;
	    foreach my $file (@runnumfiles){
		$mergefiles1 = $mergefiles1." $file";
		$nummergefiles1++;
		if( $nummergefiles1 % $NFILES==0 ){
		    $finalmergefiles1 = $finalmergefiles1 . " $DIR1/TempMerge_${runnum}_$nummergefiles1.root";
 		    if( $VERBOSE>=3 ){ print "hadd $DIR1/TempMerge_${runnum}_$nummergefiles1.root $mergefiles1\n"; }
		    system( "hadd $DIR1/TempMerge_${runnum}_$nummergefiles1.root $mergefiles1" ); #  or die "Unable to hadd: $!";
		    $mergefiles1 = "";
		}
	    }
	    if( $nummergefiles1 % $NFILES != 0 ){
		$finalmergefiles1 = $finalmergefiles1 . " $DIR1/TempMerge_${runnum}_$nummergefiles1.root";
		if( $VERBOSE>=3 ){ print "hadd $DIR1/TempMerge_${runnum}_$nummergefiles1.root $mergefiles1\n"; }
		system( "hadd ${DIR1}/TempMerge_${runnum}_${nummergefiles1}.root $mergefiles1" );#  or die "Unable to hadd: $!";
	    }
	    if( $VERBOSE>=3 ){ print "hadd ${NAME}_$runnum.root $finalmergefiles1\n";
			       print "Continue (y/n):";
			       my $input = <STDIN>;
			       chomp $input;
			       if( $input ne "y" ){ exit(0); }
	    }
	    system( "hadd $DIR1/${NAME}_$runnum.root $finalmergefiles1" );#  or die "Unable to hadd: $!";
	}
    }
    print "Total files processed: $numfiles\n";
    exit(0);
}

if( ! $DIR2 ){
    if( $numfiles % $NFILES != 0 ){
	#print "hadd StFcsPi0invariantmass$numfiles.root$mergefiles\n";
	$finalmergefiles1 = $finalmergefiles1 . " $DIR1/Merge$numfiles.root";
	if( !$TEST ){ system( "hadd -f $DIR1/Merge$numfiles.root$mergefiles1" ); }# or die "Unable to hadd: $!";
    }
    
    if( !$TEST ){ system( "hadd -f $DIR1/${NAME}.root${finalmergefiles1}" ); }
    print "Merged $numfiles files in $DIR1 to ${NAME}.root\n";
    exit(0);
}

if( $DIR2 ){
    opendir my $dh2, $DIR2 or die "Could not open '$DIR2' for reading '$!'";
    if( $VERBOSE>=1 ){ print "Reading $DIR2\n"; }
    while( my $mudstfile = readdir $dh2 ){
	if( $mudstfile =~ m/${FILTER}_(\d{8})_raw_(\d{7}).root/ ){
	    my $runnum = $1;
	    my $iternum = $2;
	    #my $iternum = $mudstfile;
	    #print "B: $iternum\n";
	    #$iternum =~ s/${FILTER}_//;
	    #$iternum =~ s/.root//;
	    #print "A: $iternum\n";
	    if( exists $Compare{$iternum} ){
		$Compare{$iternum} = 0; #0 (false) if in both
		if( $VERBOSE>=3 ){ print "$iternum exists in both directories\n"; }
	    }
	    else{
		$Compare{$iternum} = 2;  #2 (true) since it is in DIR2
		if( $VERBOSE>=2 ){print "'$iternum' is missing from dir1:$DIR1\n";}
	    }
	}
    }
    closedir $dh2;
}

if( $TEST ){ exit(0); }

if( $VERBOSE>=1 ){ print "Merging files in '$DIR1' and '$DIR2'\n"; }
$numfiles = 0;
my $mergefiles2 = "";
my $finalmergefiles2 = "";
foreach my $key (keys %Compare){
    #if( $Compare{$key} ){ print "$key:Dir$Compare{$key}\n"; }
    if( ! $Compare{$key} ){
	$mergefiles1 = $mergefiles1." $DIR1/${FILTER}_$key.root";
	$mergefiles2 = $mergefiles2." $DIR2/${FILTER}_$key.root";
	$numfiles++;
    }
    if( $numfiles % $NFILES==0 ){
	#print "hadd StFcsPi0invariantmass$numfiles.root$mergefiles\n";
	#print "$numfiles\n";
	$finalmergefiles1 = $finalmergefiles1 . " $DIR1/Merge$numfiles.root";
	$finalmergefiles2 = $finalmergefiles2 . " $DIR2/Merge$numfiles.root";
	if( !$TEST ){ system( "hadd -f $DIR1/Merge$numfiles.root$mergefiles1" ); }# or die "Unable to hadd: $!";
	if( !$TEST ){ system( "hadd -f $DIR2/Merge$numfiles.root$mergefiles2" ); }# or die "Unable to hadd: $!";
	$mergefiles1 = "";
	$mergefiles2 = "";
    }
    #if( $numfiles==101 ){last;}
}

if( $numfiles % $NFILES != 0 ){
    #print "hadd StFcsPi0invariantmass$numfiles.root$mergefiles\n";
    $finalmergefiles1 = $finalmergefiles1 . " $DIR1/Merge$numfiles.root";
    $finalmergefiles2 = $finalmergefiles2 . " $DIR2/Merge$numfiles.root";
    if( !$TEST ){ system( "hadd -f $DIR1/Merge$numfiles.root$mergefiles1" ); }# or die "Unable to hadd: $!";
    if( !$TEST ){ system( "hadd -f $DIR2/Merge$numfiles.root$mergefiles2" ); }# or die "Unable to hadd: $!";
}

if( !$TEST ){ system( "hadd -f $DIR1/${NAME}.root${finalmergefiles1}" ); }
if( !$TEST ){ system( "hadd -f $DIR2/${NAME}.root${finalmergefiles2}" ); }

print "Total files processed: $numfiles\n";

