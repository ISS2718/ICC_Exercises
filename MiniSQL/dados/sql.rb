#/usr/bin/ruby

line = readline
select = nil
from = nil
where = nil
if line.match(/select (\S.*\S) from (.*\S)/)
	select = $1
	from = $2
	if from.match(/(.*\S) where (\S.*\S)/)
		from = $1
		where = $2
	end
end

select = select.split(/\s*,\s*/)
from = from.split(/\s*,\s*/)
if where
	where = where.split(/\s+and\s+/)
else
	where = []
end

whererel = where.select{|w| w.match(/(\S+\.\S+)\s*=\s*(\S+\.\S+)/)}
whereval = where - whererel
whererel = whererel.map{|w| w.split(/\s*=\s*/)}
whereval = whereval.map{|w| w.match(/(\S+\.\S+)\s*=\s*"(.*)"/); [$1, $2]}

files = {}
from.each do |f|
	File.open("#{f}.tsv", "r") do |file|
		files[f] = []
		headers = file.readline.chomp.split(/\t/)
		file.readlines.each do |line|
			values = line.chomp.split(/\t/)
			row = {}
			headers.zip(values).each do |k,v|
				row["#{f}.#{k}"] = v
			end
			files[f] << row
		end
	end
end

res = []
firstFrom = from.first
restFrom = from.slice(1, from.length)
files[firstFrom].each do |row|
	if whererel.select{|e1, e2| ([e1, e2] - row.keys).length == 0}.all?{|e1, e2| row[e1] == row[e2]}
		if whereval.select{|e1| ([e1] - row.keys).length == 0}.all?{|e1, e2| row[e1] == e2}
			res << row
		end
	end
end

restFrom.each do |f|
	puts "#{res.length}"
	newRes = []
	files[f].product(res).each do |r1, r2|
		r = {}
		r1.keys.each do |k|
			r[k] = r1[k]
		end
		r2.keys.each do |k|
			r[k] = r2[k]
		end
		if whererel.select{|e1, e2| ([e1, e2] - r1.keys - r2.keys).length == 0}.all?{|e1, e2| r[e1] == r[e2]}
			if whereval.select{|e1| ([e1] - r1.keys - r2.keys).length == 0}.all?{|e1, e2| r[e1] == e2}
				newRes << r
			end
		end
	end
	res = newRes
end

res.each do |row|
	if whererel.all?{|e1, e2| row[e1] == row[e2]} and whereval.all?{|e1, e2| row[e1] == e2}
		puts select.map{|k| row[k]}.join("\t")
	end
end
