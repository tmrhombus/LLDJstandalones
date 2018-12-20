def get_samples():
    my_sample_list = []
    submitfile = open("../../submitters/submitjobs.sh", "r")
    startsubmitlist = False 
    for line in submitfile:

        if ")" in line:
            break
        
        if startsubmitlist:
        #skip commented
            if "#" in line: #should actually check if first non white space char
                continue
            
            line = line.replace('"', '')
            line = line.replace(' ', '')
            line = line.replace('\\', '')
            line = line.rstrip()
            
            #print(line)
            my_sample_list.append(line)

        if "samples=(" in line:
            startsubmitlist = True

    return my_sample_list
    


sample_list = get_samples()
#print(sample_list)

for sample in sample_list:
    samplefile = open('../../lists/' + sample + '.list', 'r')
    
    category_list = []

    for line in samplefile:
        values = line.split('/')
        if len(values)<8:#basically just catches new line
            continue
        category = values[7]
        category = category.replace('crab_','')

        if category not in category_list:
            category_list.append(category)
    
    #print(category_list)

    for category in category_list:
        dasmapAODfile = open('dasmapAOD.list', 'r')
        for line in dasmapAODfile:
            match = False
            values = line.split()
            for value in values:
                if category == value:
                    match = True

                if "/AOD" in value and match:
                    print value
    



