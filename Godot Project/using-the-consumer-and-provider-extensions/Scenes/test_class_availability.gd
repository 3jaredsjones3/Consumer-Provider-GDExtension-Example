extends Node

func _ready():
	# Check if files exist
	print("Consumer file exists: ", FileAccess.file_exists("res://gdextension/consumer_example.gdextension"))
	print("Consumer DLL exists: ", FileAccess.file_exists("res://gdextension/windows/libConsumerExample.windows.template_debug.x86_64.dll"))
	
	var consumer = ConsumerExample.new()
	var provider = ProviderExample.new()
	consumer.set_provider(provider)
	
	var p = consumer.process_value(0)
	
	print(p)
