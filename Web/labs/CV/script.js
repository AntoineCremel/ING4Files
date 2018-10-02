function closeSection(id){
	/*
	This function will be called onclick on each section title.
	It will close or open the content of the section.
		Parameters :
			id is the id of the section which calls this function
	*/
	// We select the corresponding section
	var section = document.getElementById(id);
	// We get the childnodes of the section
	var child = section.firstElementChild.nextElementSibling;

	/* Loop through all of the element childs of section to
	 give them the class hidden */
	 while(child){
	 	if(child.classList.contains("hidden")){
	 		child.classList.remove("hidden");
	 	}
	 	else{
	 		child.classList.add("hidden");
	 	}
	 	
	 	child = child.nextElementSibling;
	 }

	 return false;
}

function clickSubmit(){
	/*
	This function will display an alert to the user
	*/
	var confirmed = confirm("Voulez vous continuer ?\nVotre addresse est : " +
		document.getElementById("mail").value);

	return false;
}

function addJob(){
	/*
	This function will add a job description to the list, using the contents
	of the form as its base
	*/
	// Get the id of the job history dl
	var dl = document.getElementById('emp_list');

	// Get the dates in the date fields
	var start_date = document.getElementById('job_start').value;
	var end_date = document.getElementById('job_end').value;
	// Get the job description
	var job_description = document.getElementById('job_description').value;

	// Create the new dt containing the date
	var dt = document.createElement("dt");
	var dates = document.createTextNode("Du "+start_date+" au "+end_date);
	dt.appendChild(dates);

	// Create the description of the job
	var dd = document.createElement("dd");
	var descr = document.createTextNode(job_description);
	dd.appendChild(descr);

	// Add the elements to the dl
	dl.appendChild(dt);
	dl.appendChild(dd);

	return false;
}