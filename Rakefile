gem 'rake', '>= 0.8.7'
require 'rake/clean'

CXX="g++"
CFLAGS="-Werror"

task :default => [:build] do
end

EXECS = []
GENS = []

def rule_gnu_compilers(compiler, srcfile)
  objfile = File.basename(srcfile).ext('o')
  depfile = '.' + File.basename(srcfile).ext('d')

  GENS << objfile
  CLOBBER.include(objfile)
  GENS << depfile
  CLOBBER.include(depfile)

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

  file depfile => objfile do
  end
end

def rule_cpp(srcfile)
  rule_gnu_compilers(CXX, srcfile)
end

def rule_bison(srcfile)
  generated_file = File.basename(srcfile).ext('tab.cc')
  header_file = File.basename(srcfile).ext('tab.hh')

  GENS << generated_file
  CLOBBER.include(generated_file)
  GENS << header_file
  CLOBBER.include(header_file)

  file generated_file => srcfile do
    sh "bison -o #{generated_file} #{srcfile}"
  end

  file header_file => generated_file do
  end

  rule_cpp(generated_file)
end

def rule_flex(srcfile)
  generated_file = File.basename(srcfile).ext('yy.cc')

  GENS << generated_file
  CLOBBER.include(generated_file)

  file generated_file => srcfile do
    sh "flex -o #{generated_file} #{srcfile}"
  end

  rule_cpp(generated_file)
end

def rule_executable(name, sources)
  EXECS << name
  CLOBBER.include(name)

  file name => sources do |t|
    sh "#{CXX} #{CFLAGS} -o #{t.name} #{t.prerequisites.join(" ")}"
  end
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

rule_executable("fran", ["fran.o", "parser.tab.o", "lexer.yy.o"])
rule_executable("expr_test", ["expr_test.o", "ast.o"])

task :gens => GENS
task :execs => EXECS

task :build => [:gens, :execs] do
end

task :test => [:build] do
end

CLEAN.existing!
CLOBBER.existing!
