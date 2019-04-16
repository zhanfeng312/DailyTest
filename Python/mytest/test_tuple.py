t = (11, 22, ["alex", {"k1":"v1"}])

t[2][1]["k2"] = 123
print(t)

t[2][1].update({"k3":123})
print(t)