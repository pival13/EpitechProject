#!/usr/bin/env perl
use strict;
use warnings;
use List::Util "min";

my $len = @ARGV;
if ($len != 3) { print "Bad argument: 3 exepected, got $len\n"; exit 84; }
elsif ($ARGV[0] !~ /^\d+$/ or $ARGV[1] !~ /^\d+$/) { print "First and second arguments must be integers\n"; exit 84; }
elsif ($ARGV[2] !~ /^\d+(\.\d+)?$/) { print "Third argument must be a floating point number\n"; exit 84; }
elsif ($ARGV[0] < $ARGV[1] or min(@ARGV) == 0) { print "First argument must be greater than second, and both must be > 0\n"; exit 84; }
elsif ($ARGV[2] > 100) { print "Third argument must be < 100\n"; exit 84; }

my ($N, $n, $p) = @ARGV;
$p /= 100;
my $v = (($p*(1-$p)) / $n) * (($N-$n) / ($N-1));

printf "Population size:         $N\n";
printf "Sample size:             $n\n";
printf "Voting intentions:       %.2f%%\n", $p*100;
printf "Variance:                %.6f\n", $v;
printf "95%% confidence interval: [%.2f%%; %.2f%%]\n", 
    (1.96*sqrt($v) < $p) ? ($p - 1.96*sqrt($v))*100 : 0, 
    ($p + 1.96*sqrt($v) < 1) ? ($p + 1.96*sqrt($v))*100 : 100;
printf "99%% confidence interval: [%.2f%%; %.2f%%]\n", 
    (2.58*sqrt($v) < $p) ? ($p - 2.58*sqrt($v))*100 : 0, 
    ($p + 2.58*sqrt($v) < 1) ? ($p + 2.58*sqrt($v))*100 : 100;