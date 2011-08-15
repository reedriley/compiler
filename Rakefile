gem 'rake', '>= 0.8.7'
require 'rake/clean'

CXX="g++"
CPPFLAGS="-Wall -Werror `llvm-config --cppflags`"
LDFLAGS="-lgtest `llvm-config --ldflags --libs core`"

task :default => [:build] do
end

EXECS = []
GENS = []

def rule_cpp(srcfile)
  objfile = File.basename(srcfile).ext('o')
  depfile = '.' + File.basename(srcfile).ext('d')

  GENS << objfile
  CLEAN.include(objfile)
  GENS << depfile
  CLEAN.include(depfile)

  dependencies = [srcfile]

  if (File.exists?(depfile))
    File.open(depfile) do |deps|
      while line = deps.gets
        line.split(%r{\s+|:|\\$}).each do |dep|
          if !dep.empty? && dep != objfile
            dependencies << dep
          end
        end
      end
    end
  end
  
  file objfile => dependencies do
    sh "#{CXX} #{CPPFLAGS} -c -o #{objfile} #{srcfile} -MD -MF #{depfile}"
  end

  file depfile => objfile do
  end
end

def rule_bison(srcfile)
  generated_file = File.basename(srcfile).ext('tab.cpp')
  header_file = File.basename(srcfile).ext('tab.hpp')

  GENS << generated_file
  CLEAN.include(generated_file)
  GENS << header_file
  CLEAN.include(header_file)

  file generated_file => srcfile do
    sh "bison -o #{generated_file} #{srcfile}"
  end

  file header_file => generated_file do
  end

  rule_cpp(generated_file)
end

def rule_flex(srcfile)
  generated_file = File.basename(srcfile).ext('yy.cpp')

  GENS << generated_file
  CLEAN.include(generated_file)

  file generated_file => srcfile do
    sh "flex -o #{generated_file} #{srcfile}"
  end

  rule_cpp(generated_file)
end

def rule_executable(name, sources)
  EXECS << name
  CLEAN.include(name)

  file name => sources do |t|
    sh "#{CXX} #{LDFLAGS} -o #{t.name} #{t.prerequisites.join(" ")}"
  end
end

FileList['*.cpp'].each do |srcfile|
  rule_cpp(srcfile)
end

FileList['*.y'].each do |srcfile|
  rule_bison(srcfile)
end

FileList['*.l'].each do |srcfile|
  rule_flex(srcfile)
end

rule_executable("fran", ["fran.o", "parser.tab.o", "lexer.yy.o"])
rule_executable("expr_test", ["expr_test.o", "expressions.o", "declarations.o", "statements.o"])

desc "build everything"
task :build => EXECS

desc "test everything"
task :test => [:build]

CLEAN.existing!
