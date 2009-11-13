#!/usr/bin/perl

$own_file = 0;

print '
set terminal postscript color solid
set output "allplots.ps"

set style line 1 lt 1 lw 1
set style line 2 lt 2 lw 1
set style line 3 lt 3 lw 1
set style line 4 lt 4 lw 1
set style line 5 lt 5 lw 1
set style line 6 lt 6 lw 1
set style line 7 lt 7 lw 1
set style line 8 lt 8 lw 1
set style line 9 lt 9 lw 1

set grid

set xlabel "Number of neurons in the four layers"
set ylabel "Nanoseconds per connection"

set logscale
';

if($own_file)
{
    print 'set output "performance.ps"';
}

print '
set title "Performance of execution"
plot "fann_performance.out" title "fann" with lines -1, \
 "fann_stepwise_performance.out" title "fann (stepwise)" with lines 2, \
 "fann_fixed_performance.out" title "fann (fix)" with lines 1, \
 "lwnn_performance.out" title "lwnn" with lines 8, \
 "jneural_performance.out" title "jneural" with lines 9

set nologscale

set xlabel "Seconds of training"
set ylabel "Mean square error"
';

sub print_plot_line {
  local($filename, $title, $extra_title, $width, $last) = @_;

  print " \"$filename\" title \"$title $extra_title\" w l lt $linestyle lw $width";
  if(!$last)
  {
      print ", \\\n";
  }

  $linestyle++;
}


sub print_plot_lines {
  local($train_file, $train_test, $extra_title, $width) = @_;
  $linestyle = 1;

  print_plot_line("$train_file.fann_cascade_rprop_one_activation.$train_test.out", "Cascade2 RPROP One", $extra_title, $width, 0);
  print_plot_line("$train_file.fann_cascade_rprop_multi_activation.$train_test.out", "Cascade2 RPROP Multi", $extra_title, $width, 0);
  print_plot_line("$train_file.fann_cascade_quickprop_one_activation.$train_test.out", "Cascade2 Quickprop One", $extra_title, $width, 0);
  print_plot_line("$train_file.fann_cascade_quickprop_multi_activation.$train_test.out", "Cascade2 Quickprop Multi", $extra_title, $width, 0);
  print_plot_line("$train_file.fann_rprop.$train_test.out", "iRPROP-", $extra_title, $width, 0);
  #print_plot_line("$train_file.fann_rprop_stepwise.$train_test.out", "fann rprop (stepwise)", $extra_title, $width, 0);
  print_plot_line("$train_file.fann_quickprop.$train_test.out", "Quickprop", $extra_title, $width, 0);
  print_plot_line("$train_file.fann_batch.$train_test.out", "Batch", $extra_title, $width, 0);
  #print_plot_line("$train_file.fann_incremental.$train_test.out", "fann incremental", $extra_title, $width, 0);
  print_plot_line("$train_file.fann_incremental_momentum.$train_test.out", "Incremental", $extra_title, $width, 0);
  print_plot_line("$train_file.lwnn.$train_test.out", "(External) Lwnn Incremental", $extra_title, $width, 0);
  print_plot_line("$train_file.jneural.$train_test.out", "(External) Jneural Incremental", $extra_title, $width, 1);
}


sub print_plot {
  local($train_file, $logscale, $have_test, $have_train, $own_file) = @_;

  print "\nset $logscale\n";

  if($own_file)
  {
      print "set output \"$train_file.ps\"\n";
  }

  print "set title \"$train_file\"\n";
  print "plot ";
  
  if($have_train)
  {
      if($have_test)
      {
	  &print_plot_lines($train_file, "train", "Train", 2);
      } else {
	  &print_plot_lines($train_file, "train", "", 2);
      }
  }

  if($have_test)
  {
      print ", \\\n";
      if($have_test)
      {
	  &print_plot_lines($train_file, "test", "Test", 1);
      } else {
	  &print_plot_lines($train_file, "test", "", 1);
      }
  }

  print "\nset nologscale\n";
}

for($own_file = 0; $own_file < 2; $own_file++)
{
    &print_plot("abelone", "logscale x", 1, 1, $own_file);
    &print_plot("bank32fm", "logscale x", 1, 1, $own_file);
    &print_plot("bank32nh", "logscale x", 1, 1, $own_file);
    &print_plot("building", "logscale x", 1, 1, $own_file);
    &print_plot("census-house", "logscale x", 1, 1, $own_file);
    &print_plot("diabetes", "logscale x", 1, 1, $own_file);
    &print_plot("gene", "logscale x", 1, 1, $own_file);
    &print_plot("kin32fm", "logscale x", 1, 1, $own_file);
    &print_plot("mushroom", "logscale x", 1, 1, $own_file);
    &print_plot("parity8", "logscale x", 0, 1, $own_file);
    &print_plot("parity13", "logscale x", 0, 1, $own_file);
    &print_plot("pumadyn-32fm", "logscale y", 1, 1, $own_file);
    &print_plot("robot", "logscale", 1, 1, $own_file);
    &print_plot("soybean", "logscale x", 1, 1, $own_file);
    &print_plot("thyroid", "logscale y", 1, 1, $own_file);
    &print_plot("two-spiral", "logscale x", 1, 1, $own_file);
}


print "\nset output\n";
print "set terminal x11\n"
