antet = "uniform vec3"

# '''
# int light_position_spot = glGetUniformLocation(shader->program, "light_position_spot");
# 	glUniform3f(light_position_spot, lightPosition_spot.x, lightPosition_spot.y, lightPosition_spot.z);

# 	int light_direction_spot = glGetUniformLocation(shader->program, "light_direction_spot");
# 	glUniform3f(light_direction_spot, lightDirection_spot.x, lightDirection_spot.y, lightDirection_spot.z);

#  '''
vect = list()

vect.append("light_position_spot_");
vect.append("light_direction_spot_");

for i in range(0,10):
    # for z in vect:
    #     comp1 ='''int '''+z+str(i+1)+'''= glGetUniformLocation(shader->program, "''' + z +str(i+1)+'''");'''
    #     inter = z + str(i+1);
    #     comp2 ='''glUniform3f(''' + z +str(i+1)+","+inter+".x, "+inter+".y, "+inter+".z); "; 
    #     print(comp1);
    #     print(comp2);
    compose1 = "light_direction_spot_" + str(i) +";"
    compose2 = "light_position_spot_" + str(i)  +";"
    print(antet, compose1)
    print(antet, compose2)
