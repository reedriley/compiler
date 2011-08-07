gem 'rake', '>= 0.8.7'
require 'rake/clean'

task :default => [:build] do
end

CLEAN.include('*.o')
CLEAN.include('.*.d')

SRC = FileList['*.cpp']
OBJ = SRC.ext('o')

SRC.each do |srcfile|
  objfile = File.basename(srcfile).ext('o')
  depfile = '.' + File.basename(srcfile).ext('d')

  if (File.exists?(depfile))
    dependencies = []
    File.open(depfile) do |deps|
      while line = deps.gets
        line.split(%r{\s+|:|\\$}).each do |dep|
          dependencies << dep if !dep.empty?
        end
      end
    end
    dependencies.delete_at(0)
  else
    dependencies = [srcfile]
  end

  file objfile => dependencies do
    sh "g++ -c -o #{objfile} #{srcfile} -MD -MF #{depfile}"
  end
end

CLOBBER.include("fran")
file "fran" => OBJ do |t|
  sh "g++ -o #{t.name} #{OBJ}"
end

task :build => ["fran"] do
end

task :test => [:build] do
end
