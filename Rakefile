gem 'rake', '>= 0.8.7'
require 'rake/clean'

task :default => [:build] do
end

def rule_gnu_compilers(compiler, srcfile)
  objfile = File.basename(srcfile).ext('o')
  depfile = '.' + File.basename(srcfile).ext('d')

  CLEAN << objfile if File.exists? objfile
  CLEAN << depfile if File.exists? depfile

  dependencies = [srcfile]

  if (File.exists?(depfile))
    File.open(depfile) do |deps|
      while line = deps.gets
        line.split(%r{\s+|:|\\$}).each do |dep|
          dependencies << dep if !dep.empty? && dep != objfile
        end
      end
    end
  end
  
  file objfile => dependencies do
    sh "#{compiler} -c -o #{objfile} #{srcfile} -MD -MF #{depfile}"
  end
end

def rule_c(srcfile)
  rule_gnu_compilers("gcc", srcfile)
end

def rule_cpp(srcfile)
  rule_gnu_compilers("g++", srcfile)
end

def rule_bison(srcfile)
  generated_file = File.basename(srcfile).ext('tab.c')

  CLEAN << generated_file if File.exists? generated_file

  file generated_file => srcfile do
    sh "bison #{srcfile}"
  end

  rule_c(generated_file)
end

FileList['*.cpp'].each do |srcfile|
  rule_cpp(srcfile)
end

FileList['*.c'].each do |srcfile|
  rule_c(srcfile)
end

FileList['*.y'].each do |srcfile|
  rule_bison(srcfile)
end


CLOBBER.include("fran")

file "fran" => ["fran.o", "parser.tab.o"] do |t|
  sh "g++ -o fran fran.o parser.tab.o"
end

task :build => ["fran"] do
end

task :test => [:build] do
end
