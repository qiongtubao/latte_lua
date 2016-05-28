function add (x, y)
  return x + y
end
function join (x, y)
  return x.." "..y
end
function counting()
  for index = 1, 50000 do
    print(index, "+")
  end
end
function array(x, y)
  print("size: ",#x);
  for l = 0, #(y) do
    x[1+#x] = y[l]
  end
  return x;
end
function isOK(a)
  return not a;
end
function t(x, y)
  for key, value in pairs(y) do
    x[key] = value
  end
  return x;
end
function get()
  tt = {"hello" ,33}
  value = 4
  tab = {["tt"] = tt ,key = value, ["flag" ] = nil, 11}
  return tab;
end
function set(x)
  return x;
end