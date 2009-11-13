#!/usr/bin/perl
use Data::Dumper;
use POSIX;
use Math::BigFloat;

$path = "/home/lukesky/rl-thesis/doc";

@algorithms = ({ALGO => 'fann_cascade_rprop_one_activation', NAME => 'C2 RPROP One'},
	       {ALGO => 'fann_cascade_rprop_multi_activation', NAME => 'C2 RPROP Multi'},
	       {ALGO => 'fann_cascade_quickprop_one_activation', NAME => 'C2 Quickprop One'},
	       {ALGO => 'fann_cascade_quickprop_multi_activation', NAME => 'C2 Quickprop Multi'},
	       {ALGO => 'fann_rprop', NAME => 'iRPROP$^{-}$'},
	       {ALGO => 'fann_quickprop', NAME => 'Quickprop'},
	       {ALGO => 'fann_batch', NAME => 'Batch'},
	       {ALGO => 'fann_incremental_momentum', NAME => 'Incremental'},
	       {ALGO => 'lwnn', NAME => 'Lwnn Incr.'},
	       {ALGO => 'jneural', NAME => 'Jneural Incr.'});

#This is not used yet
%dataSetType = {'abelone' => 'R',
		'bank32fm' => 'R',
		'bank32nh' => 'R',
		'kin32fm' => 'R',
		'census-house' => 'R',
		'building' => 'R',
		'diabetes' => 'C',
		'gene' => 'C',
		'mushroom' => 'C',
		'parity8' => 'C',
		'parity13' => 'C',
		'pumadyn-32fm' => 'R',
		'robot' => 'R',
		'soybean' => 'C',
		'thyroid' => 'C',
		'two-spiral' => 'C'};
		

$oldDataSet = "";
$numDataSet = 0;

while(<>)
{
    chop;
    @data = split / /;
    @words = split(/\./, @data[0]);
    $dataSet = @words[0];
    $algoritm = @words[1];
    $test_train = @words[2];
    $mse = Math::BigFloat->new(@data[2]);
    $meanbitfail = Math::BigFloat->new(@data[5]);

    if($oldDataSet ne $dataSet && $oldDataSet ne "")
    {
	$numDataSet++;
	print "**$oldDataSet**\n";
	@test = keys(%summary);

	#calculate min and max mse
	$min_test_mse = 100;
	$min_train_mse = 100;
	$max_test_mse = -100;
	$max_train_mse = -100;
	while(($algo, $foo) = each(%summary))
	{
	    if($foo->{'test'} < $min_test_mse)
	    {
		$min_test_mse = $foo->{'test'};
	    }
	    if($foo->{'train'} < $min_train_mse)
	    {
		$min_train_mse = $foo->{'train'};
	    }
	    if($foo->{'test'} > $max_test_mse)
	    {
		$max_test_mse = $foo->{'test'};
	    }
	    if($foo->{'train'} > $max_train_mse)
	    {
		$max_train_mse = $foo->{'train'};
	    }
	}

	#Adds rank to each set and calculates percent etc.
	for($i = 1; $i <= scalar(%summary)+2; $i++)
	{
	    $min_algo_test = 0;
	    $min_algo_train = 0;

	    while(($algo, $foo) = each(%summary))
	    {
		if(!exists($foo->{'test_rank'}) && (!$min_algo_test || $foo->{'test'} < $summary{$min_algo_test}->{'test'}))
		{
		    $min_algo_test = $algo;
		}
		
		if(!exists($foo->{'train_rank'}) && (!$min_algo_train || $foo->{'train'} < $summary{$min_algo_train}->{'train'}))
		{
		    $min_algo_train = $algo;
		}
	    }

	    $summary{$min_algo_test}->{'test_rank'} = $i;
	    $summary{$min_algo_train}->{'train_rank'} = $i;
	    $summary{$min_algo_test}->{'test_percent'} = (($summary{$min_algo_test}->{'test'}-$min_test_mse)*100)/($max_test_mse-$min_test_mse);
	    $summary{$min_algo_train}->{'train_percent'} = (($summary{$min_algo_train}->{'train'}-$min_train_mse)*100)/($max_train_mse-$min_train_mse);
	}

	#write tex to file
	open(OUT, "> $path/".$oldDataSet."_table.tex") or die("unable to open file $path/".$oldDataSet."_table.tex");
	
	print OUT '\begin{tabular} {|l|r|r|r|r|r|r|}'."\n";
	print OUT '\hline'."\n";
	print OUT '& \multicolumn{3}{c|}{\textbf{Best Train}} & \multicolumn{3}{c|}{\textbf{Best Test}} \\\\'."\n";
	print OUT '\hline'."\n";
	print OUT '\textbf{Configuration} & \textbf{MSE} & \textbf{Rank} & \textbf{\%} & \textbf{MSE} & \textbf{Rank} & \textbf{\%} \\\\'."\n";
	print OUT '\hline'."\n";

	foreach $algo (@algorithms)
	{ 
	    $foo = $summary{$algo->{ALGO}};
	    printf OUT ("%s & %.8f & %d & %.2f & %.8f & %d & %.2f\\\\\n\\hline\n", 
		   $algo->{NAME}, 
		   $foo->{'train'}, $foo->{'train_rank'}, $foo->{'train_percent'}, 
		   $foo->{'test'}, $foo->{'test_rank'}, $foo->{'test_percent'});

	    $total{$algo->{ALGO}}->{'train'} += $foo->{'train'};
	    $total{$algo->{ALGO}}->{'test'} += $foo->{'test'};
	    $total{$algo->{ALGO}}->{'train_percent'} += $foo->{'train_percent'};
	    $total{$algo->{ALGO}}->{'test_percent'} += $foo->{'test_percent'};
	    $total{$algo->{ALGO}}->{'train_rank'} += $foo->{'train_rank'};
	    $total{$algo->{ALGO}}->{'test_rank'} += $foo->{'test_rank'};
	}
	print OUT '\end{tabular}'."\n";
	close(OUT);

	undef(%summary);
    }

    $summary{$algoritm}->{$test_train} = $mse;
    $oldDataSet = $dataSet;
}

print "**Average**\n";
open(OUT, "> $path/average_table.tex") or die("unable to open file $path/average_table.tex");
print OUT '\begin{tabular} {|l|r|r|r|r|r|r|}'."\n";
print OUT '\hline'."\n";
print OUT '& \multicolumn{3}{c|}{\textbf{Best Train}} & \multicolumn{3}{c|}{\textbf{Best Test}} \\\\'."\n";
print OUT '\hline'."\n";
print OUT '\textbf{Configuration} & \textbf{MSE} & \textbf{Rank} & \textbf{\%} & \textbf{MSE} & \textbf{Rank} & \textbf{\%} \\\\'."\n";
print OUT '\hline'."\n";
foreach $algo (@algorithms)
{
    $foo = $total{$algo->{ALGO}};
    printf OUT ("%s & %.6f & %.2f & %.2f & %.6f & %.2f & %.2f\\\\\n\\hline\n", 
	   $algo->{NAME}, 
	   $foo->{'train'}/$numDataSet, $foo->{'train_rank'}/$numDataSet, $foo->{'train_percent'}/$numDataSet, 
	   $foo->{'test'}/$numDataSet, $foo->{'test_rank'}/$numDataSet, $foo->{'test_percent'}/$numDataSet);
}
	print OUT '\end{tabular}'."\n";
close(OUT);
