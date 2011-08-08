gem 'rake', '>= 0.8.7'
require 'rake/clean'

CFLAGS=""

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
    sh "#{compiler} #{CFLAGS} -c -o #{objfile} #{srcfile} -MD -MF #{depfile}"
  end
end

def rule_cpp(srcfile)
  rule_gnu_compilers("g++", srcfile)
end

def rule_bison(srcfile)
  generated_file = File.basename(srcfile).ext('tab.cc')
  header_file = File.basename(srcfile).ext('tab.hh')

  CLEAN << generated_file if File.exists? generated_file
  CLEAN << header_file if File.exists? header_file

  file generated_file => srcfile do
    sh "bison -o #{generated_file} #{srcfile}"
  end

  rule_cpp(generated_file)
end

def rule_flex(srcfile)
  generated_file = File.basename(srcfile).ext('yy.cc')

  CLEAN << generated_file if File.exists? generated_file

  file generated_file => srcfile do
    sh "flex -o #{generated_file} #{srcfile}"
  end

  rule_cpp(generated_file)
end

FileList['*.cc'].each do |srcfile|
  rule_cpp(srcfile)
end

FileList['*.y'].each do |srcfile|
  rule_bison(srcfile)
end

FileList['*.l'].each do |srcfile|
  rule_flex(srcfile)
end

CLOBBER.include("fran")

file "fran" => ["fran.o", "parser.tab.o", "lexer.yy.o"] do |t|
  sh "g++ -o #{t.name} #{t.prerequisites.join(" ")}"
end

task :build => ["fran"] do
end

task :test => [:build] do
end
